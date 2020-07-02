#include "database.h"
Storereg::Storereg(std::string mongouri, std::string mongodb)
{
	mongocxx::instance inst{};                                          ///creating mongodb server instance
    // Storereg::client{mongocxx::uri{"mongodb://0.0.0.0:2717/" }};
    //mongocxx::database db=client["cppdb"]; 
    Storereg::dburi=mongouri;
    Storereg::dbname=mongodb;
    updatesid("sessioncoll","sid");

}

void Storereg::updatedb(bsoncxx::document::value doc_val,std::string collname)
{
    mongocxx::client client{mongocxx::uri{Storereg::dburi}}; 
    mongocxx::collection colleg=client[Storereg::dbname][collname]; 
    std::cout<<"storing in database"<<std::endl;
    colleg.insert_one(doc_val.view());
}

void Storereg::updatesid(std::string collname,std::string field)
{   mongocxx::client client{mongocxx::uri{Storereg::dburi}}; 
    mongocxx::collection colleg=client[Storereg::dbname][collname]; 
    std::cout<<"incrementing sessionID"<<std::endl;
    bsoncxx::stdx::optional<bsoncxx::document::value> result =  colleg.find_one({});
    bsoncxx::builder::stream::document doc;
    int elevalue;
    try{
        bsoncxx::document::element store_ele{result->view()[field]};
        elevalue=store_ele.get_int32().value;
    }
    catch(bsoncxx::v_noabi::exception& e)
    {
        std::cout<<e.what()<<std::endl;
        
        doc<<field<<0;
        bsoncxx::document::value doc_val=doc<<bsoncxx::builder::stream::finalize;
        colleg.insert_one(doc_val.view());
        bsoncxx::document::element store_ele{result->view()[field]};
        elevalue=store_ele.get_int32().value;
    }
    colleg.update_many(doc << field << elevalue<< bsoncxx::builder::stream::finalize,
                     doc << "$set" << bsoncxx::builder::stream::open_document <<
                        field << elevalue +1 << bsoncxx::builder::stream::close_document << bsoncxx::builder::stream::finalize); 
    Storereg::sid=elevalue+1;

}
void Storereg::insertVal(const modmanipros::regval msg,const FlatMessage& fmsg)
{
    std::regex re("\/");                                                ///String manipulation e.g instval/temp --> instval_temp
    bsoncxx::builder::stream::document doc{};
    doc<<"sid"<<Storereg::sid;

    for(auto& it:fmsg.value) {
            std::string fieldname = it.first.toStdString();             ///iterating through Rosmsg fields
            double value = it.second.convert<double>();                 ///updating values to Rosmsg fields
            std::cout<<fieldname<<":"<<value<<std::endl;
            fieldname = fieldname.substr(9, fieldname.length());        
            fieldname = std::regex_replace (fieldname ,re,"$1_$2");     
            doc << fieldname << value;
    }
    
	bsoncxx::document::value doc_val = doc << bsoncxx::builder::stream::finalize;   ///updating doc_value to BSON doc object
    bsoncxx::document::view viewer = doc_val.view();
	std::cout << bsoncxx::to_json(doc_val) << std::endl;                                     
    updatedb(doc_val,"testcollection");  

}
void Storereg::insertVal(const modmanipros::alarmval msg,const FlatMessage& fmsg)
{
    std::regex re("\/");                                                ///String manipulation e.g instval/temp --> instval_temp
    bsoncxx::builder::stream::document doc{};
    doc<<"sid"<<Storereg::sid;
    std::cout<<"hai"<<std::endl;
    auto arr=doc << "severity" << bsoncxx::builder::stream::open_array;
    for(auto& it:fmsg.value) {
            std::string fieldname = it.first.toStdString();             ///iterating through Rosmsg fields
            double value = it.second.convert<double>();                 ///updating values to Rosmsg fields
            //std::cout<<fieldname<<":"<<value<<std::endl;
            fieldname = fieldname.substr(9, fieldname.length());        
            fieldname = std::regex_replace (fieldname ,re,"$1_$2"); 
            arr=arr<<value;
            //doc<<std::to_string(value);
      
            //temp=temp+to_string(value);
            //doc << fieldname << value;
    }
    auto arr2=arr<<bsoncxx::builder::stream::close_array;
    
	bsoncxx::document::value doc_val = arr2 << bsoncxx::builder::stream::finalize;   ///updating doc_value to BSON doc object
    bsoncxx::document::view viewer = doc_val.view();
	std::cout << bsoncxx::to_json(doc_val) << std::endl;                                     
    updatedb(doc_val,"testcollection2");  

}
template<typename T>
void Storereg::deserialize(const T msg)
{
    uint32_t serial_size = ros::serialization::serializationLength(msg);        
    
    std::vector<uint8_t> buffer(serial_size);                           ///Creating buffer for serialization
    
    ser::OStream stream(buffer.data(), buffer.size());
    ser::serialize(stream, msg);                                        ///Serialization of rosmsg /modmanip/readval
    RosIntrospection::Parser parser;
    const std::string topic_name = "modmanip";
    FlatMessage flat_container;
    parser.registerMessageDefinition(                                   
        topic_name,
        ROSType(DataType<T>::value()),
        Definition<T>::value());
        parser.deserializeIntoFlatContainer( topic_name,                    ///Deserialize rosmsg into ros_type_introspection Flatmessage 
                                        Span<uint8_t>(buffer),          ///Using parser
                                        &flat_container, 200 );
    Storereg::insertVal(msg, flat_container);
       
    //return flat_container;
   }


void Storereg::insertRegData(const modmanipros::regval msg)
{                       
    deserialize<modmanipros::regval>(msg);
                                    

}
void Storereg::insertAlarmData(const modmanipros::alarmval msg)
{
    deserialize<modmanipros::alarmval>(msg);
}

