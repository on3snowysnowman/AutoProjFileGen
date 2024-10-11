#include <iostream>
#include <string>

#include "JsonHandler.hpp"
#include "FileSystemHandler.hpp"
#include "TextFileHandler.hpp"
#include "TimeObserver.hpp"


// void iterate_to_add_library_token(std::istringstream& str_stream)
// {
    
//     const std::string ADD_LIBRARY_LOOKUP = "add_library";

//     std::string next_word;

//     bool non_match = false;

//     while(str_stream >> next_word)
//     {
//         // Too short to be add_library
//         if(next_word.size() < 13) continue;

//         // Iterate through each character of the parsed word and check if it matches "add_library"
//         for(int i = 0; i < 11; ++i)
//         {
//             if(next_word.at(i) != ADD_LIBRARY_LOOKUP.at(i))
//             {
//                 non_match = true;
//                 break;
//             }
//         }

//         // This word is not add_library
//         if(non_match)
//         {
//             non_match = false;
//             continue;
//         }

//         return; 
//     }

//     // Did not find add_library
//     std::cout << "[ERR] Could not find \"add_library\" token in cmake txt file.\n";
//     exit(1);
// }

// void handle_cmake_txt_insertion(std::string& cmake_txt_contents, 
//     const std::string& PRE_SYNTAX, const std::string& NEW_FILE_NAME)
// {
//     std::istringstream str_stream(cmake_txt_contents);  

//     iterate_to_add_library_token(str_stream);

//     std::string next_word;
//     bool match;

//     while(str_stream >> next_word)
//     {
//         match = true;

//         if(next_word == ")")
//         {
//             cmake_txt_contents.insert(int(str_stream.tellg()) - 1, 
//                 '\t' + PRE_SYNTAX + NEW_FILE_NAME + ".cpp\n");
//             return;
//         }

//         if(next_word.size() <= PRE_SYNTAX.size()) continue;

//         for(int i = 0; i < PRE_SYNTAX.size(); ++i)
//         {
//             if(next_word.at(i) != PRE_SYNTAX.at(i))
//             {
//                 match = false;
//                 break;
//             }
//         }

//         if(!match)
//         {
//             match = true;
//             continue;
//         }

//         // Proper pre syntax was found, check if the next character is greater in 
//         // alphabetical order

//         int index = 0;

//         match = true;

//         // Compares both strings against eachother to find which one is lexiconally smaller.
//         for(int i = 0; i < next_word.size() && i < NEW_FILE_NAME.size(); ++i)
//         {
//             if(NEW_FILE_NAME.at(i) > next_word.at(i + PRE_SYNTAX.size()))
//             {
//                 match = false;
//                 break;
//             }

//             else if(NEW_FILE_NAME.at(i) < next_word.at(i + PRE_SYNTAX.size()))
//             {
//                 match = true;
//                 break;
//             }
//         }

//         if(match)
//         {
//             // Insert the new file name here with the pre syntax.
//             cmake_txt_contents.insert(int(str_stream.tellg()) - next_word.size(), 
//                 PRE_SYNTAX + NEW_FILE_NAME + ".cpp\n\t");
//             return;
//         }
//     }
// }


int main()
{
    json config_json = JsonHandler::get("config.json");

    // Get the name of the file the user wants to create.
    std::string new_file_name = config_json.at("file_name");

    // Assign the directories for each position of the new file.
    std::string include_directory = std::string(config_json.at("include_directory"))
        + "/" + new_file_name + ".hpp";

    std::string cpp_directory = std::string(config_json.at("cpp_directory")) 
        + "/" + new_file_name + ".cpp";

    // If the user does not want to overwrite files, and a header or cpp file already exist at the
    // target path.
    if(!config_json.at("overwrite_existing_files") &&
        (FileSystemHandler::does_directory_exist(include_directory) ||
        FileSystemHandler::does_directory_exist(cpp_directory)))
    {
        std::cout << "[ERR] Header or Cpp directory already exists! Set the \"overwrite_existing"
        "_files\" to true to overwrite files.\n";
        exit(1);
    }

    // std::string cmake_txt_directory = config_json.at("cmake_txt_directory");

    // std::string cmake_cpp_syntax = config_json.at("cmake_cpp_syntax");

    // // Create the new header and cpp files at their target directories.
    // FileSystemHandler::make_file(include_directory);
    // FileSystemHandler::make_file(cpp_directory );

    // The current date (time).
    std::string date = TimeObserver::get_local_date();

    // Default cpp file contents. 
    const std::string DEF_CPP_CONTENTS =
    "/**\n"
    " * @file " + new_file_name + ".cpp\n"
    " * @author Joel Height (On3SnowySnowman@gmail.com)\n"
    " * @brief \n"
    " * @version 0.1\n"
    " * @date " + date + "\n"
    " *\n * @copyright Copyright (c) 2024\n"
    " *\n"
    " */\n\n#include \"" + new_file_name + ".hpp\"\n\n\n"
    "// Constructors / Deconstructor\n\n\n\n// Public\n\n\n\n// Private\n\n\n";

    // Default header file contents.
    const std::string DEF_HEADER_CONTENTS = 
    "/**\n"
    " * @file " + new_file_name + ".hpp\n"
    " * @author Joel Height (On3SnowySnowman@gmail.com)\n"
    " * @brief \n"
    " * @version 0.1\n"
    " * @date " + date + "\n"
    " *\n * @copyright Copyright (c) 2024\n"
    " *\n"
    " */\n\n#pragma once\n\n\n";

    // Write the default header file contents to the header file.
    TextFileHandler::add_to_buffer(DEF_HEADER_CONTENTS);
    TextFileHandler::write(include_directory);

    // Write the default cpp file contents to the cpp file.
    TextFileHandler::add_to_buffer(DEF_CPP_CONTENTS);
    TextFileHandler::write(cpp_directory);

    // std::string cmake_txt_contents = TextFileHandler::fetch(cmake_txt_directory);

    // handle_cmake_txt_insertion(cmake_txt_contents, cmake_cpp_syntax, new_file_name);

    // TextFileHandler::add_to_buffer(cmake_txt_contents);
    // TextFileHandler::write(cmake_txt_directory);

    return 0;
}
