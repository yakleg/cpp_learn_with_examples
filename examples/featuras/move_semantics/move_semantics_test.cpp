#include <gtest/gtest.h>
#include <utility>

class DataObject {
 private:
  std::string name;
  std::stringstream ss;

 public:
  DataObject(std::string name) : name{name} {
    ss << name << " was constructed with given name\n";
  };

  DataObject(DataObject& rhs) {
    ss << name << " was copy-constructed from " << rhs.name << "\n";
  };

  DataObject(DataObject&& rhs) {
    ss << name << " was move-constructed from " << rhs.name << "\n";
  };

  DataObject& operator=(DataObject& rhs) {
    ss << name << " was copy-assigned from " << rhs.name << "\n";
  }

  DataObject& operator=(DataObject&& rhs) {
    ss << rhs.ss.str();
    ss << name << " was move-assigned from " << rhs.name << "\n";
  };

  friend std::ostream& operator<<(std::ostream& out, const DataObject& rhs) {
    out << rhs.ss.str();
    return out;
  }
};

TEST(move_semantics, test_name) {
  DataObject do1{"first"};
  auto do2 = DataObject("second");
  do1 = do2;
  std::cout << do2;
  std::cout << do1;
}