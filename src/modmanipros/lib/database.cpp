#include "database.h"
Storereg::Storereg()
{
	mongocxx::instance inst{};
}
bsoncxx::document::value Storereg::deserialize(const modmanipros::regval msg)
{
        // std::string str;
        // str.append("{");
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
            //builder << fieldname << value; 
	    fieldname = fieldname.substr(9, fieldname.length());
	    //std::cout<<fieldname<<std::endl;
	    fieldname = std::regex_replace (fieldname ,re,"$1_$2");
	    //std::cout<<fieldname<<std::endl;
        //     str.append("\"");
        //     str.append(fieldname);
        //     str.append("\"");
        //     str.append(":");
        //     str.append(std::to_string(value));
        //     str.append(", ");
	    doc << fieldname << value;
        }
        // str.append("\"");
        // str.append("id");
        // str.append("\"");
        // str.append(":");
        // str.append(std::to_string(5));
        // str.append("}");
	bsoncxx::document::value doc_val = doc << bsoncxx::builder::stream::finalize;
        bsoncxx::document::view viewer = doc_val.view();
	std::cout << bsoncxx::to_json(doc_val) << std::endl;
        return doc_val;
}
void Storereg::insertRegData(const modmanipros::regval msg)
{
    // mongocxx::uri uri("mongodb://0.0.0.0:2717/");
    // mongocxx::client conn(uri);
    mongocxx::client conn{mongocxx::uri{"mongodb://0.0.0.0:2717/" }};
    bsoncxx::document::value docObj = deserialize(msg);
    //std::cout<<str<<std::endl;
    //bsoncxx::document::value bsonObj = bsoncxx::from_json(bsoncxx::stdx::string_view(str));
    
    //bsoncxx::document::view view = bsonObj.view();
    auto collection = conn["testdb"]["testcollection"];
    collection.insert_one(docObj.view());
    auto cursor = collection.find({});
    std::cout<<"printing"<<std::endl;
//     for (auto&& doc : cursor) {
//         std::cout << bsoncxx::to_json(doc) << std::endl;
//     }
}