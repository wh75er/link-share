#pragma once

#include <filesystem>
#include <fstream>

#define PACKAGE_SIZE 400

template<class Connection>
Sender<Connection>::Sender(std::shared_ptr<Connection> connection)
        : connection_(connection)
{
#ifdef DEBUG
  std::cout << "Sender constructor" << std::endl;
#endif
}

template<class Connection>
std::vector<std::string> Sender<Connection>::form_packages(std::string data, char status) {
  std::vector<std::string> pkgs;

  std::string pkg;
  if (data.size() <= PACKAGE_SIZE-1) {
    pkg += status;
    pkg += data;
    for (auto i = 0; i < PACKAGE_SIZE-1 - data.size(); i++) {
      pkg += '\x1A';
    }
    pkgs.push_back(pkg);
  } else {
    while(!data.empty()) {
      if (data.size() <= PACKAGE_SIZE-1) {
        pkg += status;
      } else {
        pkg += 'c';
      }

      pkg += data.substr(0, PACKAGE_SIZE-1);
      data.erase(0, PACKAGE_SIZE-1);

      while (pkg.size() < PACKAGE_SIZE) {
        pkg += '\x1A';
      }

      pkgs.push_back(pkg);
    }
  }

  return pkgs;
}

template<class Connection>
void Sender<Connection>::send_with_packages(std::string data, char status) {
  std::vector<std::string> pkgs = form_packages(data, status);
#ifdef DEBUG
  std::cout << "Pkgs number: " << pkgs.size() << std::endl;
#endif

  for (auto& pkg : pkgs) {
#ifdef DEBUG
    std::cout << "Pkg : " << pkg << std::endl;
#endif
    connection_->write(pkg);
  }

}

template<class Connection>
void Sender<Connection>::send(std::shared_ptr<Response>& response) {
#ifdef DEBUG
  std::cout << "Sender data: " << response->serialize() << std::endl;
#endif

  if (!response->files_dir.empty()) {
    send_with_packages(response->serialize(), 'e');
    std::string directory = response->files_dir;

    std::vector<std::string> files;

    std::filesystem::recursive_directory_iterator d_it(directory);
    std::filesystem::recursive_directory_iterator d_it_end;
    for (; d_it != d_it_end;  d_it++) {
      if (std::filesystem::is_regular_file(d_it->status())) {
        files.push_back(d_it->path());
      }
    }
    for (auto it = files.begin(); it != files.end(); it++) {
      std::string file_name = *it;
      std::string::size_type start_pos = file_name.find_last_of('/');
      files.push_back(file_name.substr(start_pos, file_name.size() - start_pos));
      send_with_packages(file_name, 'e');

#ifdef DEBUG
      std::cout << "Sending file: " << *it << std::endl;
#endif

      std::ifstream fin(it->c_str(), std::ios::binary);
      std::string data((std::istreambuf_iterator<char>(fin)),
                       std::istreambuf_iterator<char>());

      char status = 'e';
      if (std::next(it) == files.end()) {
        status = 'f';
      }

      send_with_packages(data, status);
    }
  } else {
    send_with_packages(response->serialize(), 'f');
  }

  connection_->finish();
  connection_.reset();
}
