/** @file   vise.cc
 *  @brief  main entry point for the VGG Image Search Enginer (VISE)
 *
 *  @author Abhishek Dutta (adutta@robots.ox.ac.uk)
 *  @date   31 March 2017
 */

#include <iostream>
#include <string>

#include <boost/filesystem.hpp>

#include <Magick++.h>            // to transform images

#include "ViseServer.h"

int main(int argc, char** argv) {
  std::cout << "\nVGG Image Search Engine (VISE)";
  std::cout << "\n";
  if ( argc != 3 ) {
    std::cout << "\n  Usage: ./vise VISE_SOURCE_DIR VISE_DATA_DIR\n" << std::flush;
    return 0;
  }

  //unsigned int port = 9973;
  unsigned int port = 8080;

  Magick::InitializeMagick(*argv);

/*
  std::string vise_src = getenv("VISE_SRC_DIR");
  std::string data_home = getenv("VISE_DATA_DIR");
*/

  boost::filesystem::path data_home( argv[2] );
  boost::filesystem::path path_vise_src( argv[1] );
  boost::filesystem::path vise_template = path_vise_src / "src/server/html_templates/";

  if (!boost::filesystem::exists(vise_template) ) {
    std::cout << "\nVISE_SOURCE_DIR = " << vise_template.string() << " does not exist!" << std::flush;
    std::cout << std::endl;
    return 0;
  }

  if ( !boost::filesystem::exists(data_home) ) {
    boost::filesystem::create_directories( data_home );
    std::cout << "\nCreated VISE_DATA_DIR=" << data_home.string() << std::endl;
  }

  ViseServer vise_server( data_home, vise_template );
  //vise_server.InitResources( visedata_dir, template_dir );

  vise_server.Start(port);

  // server is stopped by sending the following HTTP POST request
  // POST /
  // shutdown_vise now (the POST data)
  return 0;
}
