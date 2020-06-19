#include "database.h"
Storereg::Storereg()
{
	mongocxx::instance inst{};
    // Storereg::client{mongocxx::uri{"mongodb://0.0.0.0:2717/" }};
    //mongocxx::database db=client["cppdb"]; 


}
bsoncxx::document::value Storereg::deserialize(const modmanipros::regval msg)
{
    uint32_t serial_size = ros::serialization::serializationLength(msg);
    
    std::vector<uint8_t> buffer(serial_size);
    
    ser::OStream stream(buffer.data(), buffer.size());
    ser::serialize(stream, msg);
    RosIntrospection::Parser parser;
    const std::string topic_name = "modmanip";
    parser.registerMessageDefinition(
        topic_name,
        ROSType(DataType<modmanipros::regval>::value()),
        Definition<modmanipros::regval>::value());

    FlatMessage flat_container;
    parser.deserializeIntoFlatContainer( topic_name,
                                        Span<uint8_t>(buffer),
                                        &flat_container, 200 );
    std::regex re("\/");
    auto doc = bsoncxx::builder::stream::document{};
        for(auto& it: flat_container.value) {
            std::string fieldname = it.first.toStdString();
            double value = it.second.convert<double>();
            fieldname = fieldname.substr(9, fieldname.length());
            fieldname = std::regex_replace (fieldname ,re,"$1_$2");
            doc << fieldname << value;
        }
    
	bsoncxx::document::value doc_val = doc << bsoncxx::builder::stream::finalize;
        bsoncxx::document::view viewer = doc_val.view();
	std::cout << bsoncxx::to_json(doc_val) << std::endl;
        return doc_val;
}
void Storereg::insertRegData(const modmanipros::regval msg)
{
    mongocxx::client client{mongocxx::uri{"mongodb://0.0.0.0:2717/" }};
    mongocxx::database db= client["cppdb"];
    mongocxx::collection collect= db["testcollection"];
    bsoncxx::document::value docObj = deserialize(msg);

    collect.insert_one(docObj.view());
    auto cursor = collect.find({});
    std::cout<<"storing in database"<<std::endl;
//     for (auto&& doc : cursor) {
//         std::cout << bsoncxx::to_json(doc) << std::endl;
//     }
}
