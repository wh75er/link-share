#pragma once

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
void Sender<Connection>::send(std::shared_ptr<Response> response) {
#ifdef DEBUG
  std::cout << "Sender data: " << response->serialize() << std::endl;
#endif
  connection_->write(response->serialize());
  connection_->finish();
  connection_.reset();
}
