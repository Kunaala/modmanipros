#include "database.h"
Storereg::Storereg()
{
	mongocxx::instance inst{};                                          ///creating mongodb server instance
    // Storereg::client{mongocxx::uri{"mongodb://0.0.0.0:2717/" }};
    //mongocxx::database db=client["cppdb"]; 


}
bsoncxx::document::value Storereg::deserialize(const modmanipros::regval msg)
{
    uint32_t serial_size = ros::serialization::serializationLength(msg);        
    
    std::vector<uint8_t> buffer(serial_size);                           ///Creating buffer for serialization
    
    ser::OStream stream(buffer.data(), buffer.size());
    ser::serialize(stream, msg);                                        ///Serialization of rosmsg /modmanip/readval
    RosIntrospection::Parser parser;
    const std::string topic_name = "modmanip";
    parser.registerMessageDefinition(                                   
        topic_name,
        ROSType(DataType<modmanipros::regval>::value()),
        Definition<modmanipros::regval>::value());

    FlatMessage flat_container;
    parser.deserializeIntoFlatContainer( topic_name,                    ///Deserialize rosmsg into ros_type_introspection Flatmessage 
                                        Span<uint8_t>(buffer),          ///Using parser
                                        &flat_container, 200 );
    std::regex re("\/");                                                ///String manipulation e.g instval/temp --> instval_temp
    auto doc = bsoncxx::builder::stream::document{};
        for(auto& it: flat_container.value) {
            std::string fieldname = it.first.toStdString();             ///iterating through Rosmsg fields
            double value = it.second.convert<double>();                 ///updating values to Rosmsg fields
            fieldname = fieldname.substr(9, fieldname.length());        
            fieldname = std::regex_replace (fieldname ,re,"$1_$2");     
            doc << fieldname << value;
        }
    
	bsoncxx::document::value doc_val = doc << bsoncxx::builder::stream::finalize;   ///updating doc_value to BSON doc object
        bsoncxx::document::view viewer = doc_val.view();
	std::cout << bsoncxx::to_json(doc_val) << std::endl;            
        return doc_val;
}
void Storereg::insertRegData(const modmanipros::regval msg,std::string dburi, std::string dbname)
{

    mongocxx::client client{mongocxx::uri{dburi}};                              ///Connecting to mongosb instance
    mongocxx::database db= client[dbname];                                      ///creating mongodb object
    mongocxx::collection collect= db["testcollection"];                         
    bsoncxx::document::value docObj = deserialize(msg);                         
    std::cout<<"storing in database"<<std::endl;
    collect.insert_one(docObj.view());                                          ///inserting doc to collection
// auto cursor = collect.find({});
    
//     for (auto&& doc : cursor) {
//         std::cout << bsoncxx::to_json(doc) << std::endl;
//     }
}
