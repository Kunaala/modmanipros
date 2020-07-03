#include <iostream>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include<exception>
#include<bsoncxx/exception/exception.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>


int main(int, char**) {
    mongocxx::instance  inst{};
    mongocxx::client conn{mongocxx::uri{}};

    
    mongocxx::database db = conn["cppdb"];
    mongocxx::collection coll1 = db["colltemp"];

    bsoncxx::builder::stream::document doc{};
    doc<<"temp1"<<10<<"temp2"<<20;
    bsoncxx::document::value doc_val=doc<<bsoncxx::builder::stream::finalize;
    coll1.insert_one(doc_val.view());
    //bsoncxx::document::element store_ele{doc_val.view()["id"]};
    bsoncxx::stdx::optional<bsoncxx::document::value> result =  coll1.find_one({});
    try{
        bsoncxx::document::element store_ele{result->view()["temp1"]};
        std::cout << "as expected, we have a team"<<" "<<store_ele.get_int32().value << std::endl;
    }
    catch(bsoncxx::v_noabi::exception& e)
    {
        std::cout<<e.what()<<std::endl;
    }
    
}