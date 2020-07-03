#include <iostream>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include<exception>
#include<bsoncxx/exception/exception.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

void initialize(mongocxx::client& conn)
{
    mongocxx::collection colleg=conn["mydb"]["colleg"];
    using namespace bsoncxx::builder::stream;
    bsoncxx::builder::stream::document build_doc;
    build_doc  << "temp"<<20<<"name" << open_document << "first"
              << "John"
              << "last"
              << "Backus" << close_document << "contribs" << open_array << "Fortran"
              << "ALGOL"
              << "Backus-Naur Form"
              << "FP" << close_array << "awards" << open_array << open_document << "award"
              << "W.W. McDowell Award"
              << "year" << 1967 << "by"
              << "IEEE Computer Society" << close_document << open_document << "award"
              << "Draper Prize"
              << "year" << 1993 << "by"
              << "National Academy of Engineering" << close_document << close_array;
    bsoncxx::document::value doc_val = build_doc << bsoncxx::builder::stream::finalize;
    auto doc_view = doc_val.view();
    colleg.insert_one(doc_view);

}

int main(int, char**) {
    mongocxx::instance  inst{};
    mongocxx::client conn{mongocxx::uri{}};

    
    mongocxx::database db = conn["cppdb"];
    mongocxx::collection coll1 = db["coll1"];
    mongocxx::collection coll2 = db["coll2"];

    initialize(conn);
    
    // mongocxx::collection coll = conn["mydb"]["testcoll"];
    bsoncxx::builder::stream::document builder{};
    bsoncxx::builder::stream::document document2{};
    //auto builder = bsoncxx::builder::stream::document{};
    using namespace bsoncxx::builder::stream;
    bsoncxx::builder::stream::document build_doc;
    // {
    //     "_id" : 1,
    //     "name" : { "first" : "John", "last" : "Backus" },
    //     "contribs" : [ "Fortran", "ALGOL", "Backus-Naur Form", "FP" ],
    //     "awards" : [
    //                {
    //                  "award" : "W.W. McDowell Award",
    //                  "year" : 1967,
    //                  "by" : "IEEE Computer Society"
    //                },
    //                { "award" : "Draper Prize",
    //                  "year" : 1993,
    //                  "by" : "National Academy of Engineering"
    //                }
    //     ]
    // }
    build_doc  << "temp"<<10<<"name" << open_document << "first"
              << "John"
              << "last"
              << "Backus" << close_document << "contribs" << open_array << "Fortran"
              << "ALGOL"
              << "Backus-Naur Form"
              << "FP" << close_array << "awards" << open_array << open_document << "award"
              << "W.W. McDowell Award"
              << "year" << 1967 << "by"
              << "IEEE Computer Society" << close_document << open_document << "award"
              << "Draper Prize"
              << "year" << 1993 << "by"
              << "National Academy of Engineering" << close_document << close_array;
    bsoncxx::document::value doc_val = build_doc << bsoncxx::builder::stream::finalize;
    auto doc_view = doc_val.view();
    // coll1.insert_one(doc_view);
 
    std::cout << bsoncxx::to_json(doc_val) << std::endl;
    bsoncxx::stdx::optional<bsoncxx::document::value> result =  coll1.find_one({});
    std::cout << "duplicate"<<bsoncxx::to_json(*result) << std::endl;
    //bsoncxx::document::element store_ele{doc_view["temp"]};
    bsoncxx::document::element store_ele{result->view()["temp"]};
    try{
         bsoncxx::document::element store_elem{result->view()["id"]};
    }
    
    catch(bsoncxx::v_noabi::exception& e)
    {
        std::cout<<"exception caught"<<std::endl;
        coll1.insert_one(doc_view);
    }
   
    catch(...)
    {
        std::cout<<"hai"<<std::endl;
    }
    bsoncxx::document::element store_elem2{result->view()["id"]};
    if (store_ele) {
    // // this block will only execute if "store" was found in the document
    //std::cout << "Examining inventory at " << bsoncxx::to_json(store_ele.get_value()) << std::endl;
        std::cout << "as expected, we have a team"<<" "<<store_ele.get_int32().value << std::endl;
     }
    coll1.update_many(build_doc << "temp" << store_ele.get_int32().value<< finalize,
                     build_doc << "$set" << open_document <<
                        "temp" << store_ele.get_int32().value +2 << close_document << finalize);   
   mongocxx::cursor cursor = coll1.find({});
    for(auto it : cursor) {
     std::cout << bsoncxx::to_json(it) << "\n";
    }

}     
