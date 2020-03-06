#include <gtest/gtest.h>
#include <memory>
#include <string>

// Pure virtual interface
class Animal {
 public:
  // https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#c130-for-making-deep-copies-of-polymorphic-classes-prefer-a-virtual-clone-function-instead-of-copy-constructionassignment
  // For making deep copies of polymorphic classes prefer a
  // virtual clone function instead of copy construction/assignment
  Animal(const Animal&) = delete;
  Animal& operator=(const Animal&) = delete;

  virtual ~Animal() = default;  // MUST contain implementation of virtual destructor

  virtual std::string MakeNoise() const = 0;
  virtual int age() const = 0;
  virtual int weight() const = 0;

  using Ptr = std::unique_ptr<Animal>;

 protected:
  // One of the constructors was defined
  // We have to put implicit declaration of default constructor
  Animal() = default;
};

// Class Cat extends Animal interface
class Cat : public Animal {
 public:
  Cat(int age, int weight) : m_age{age}, m_weight{weight} {}

  // We have to override all the pure virtual methods of the base class (Animal)
  virtual std::string MakeNoise() const override { return "meow"; };
  virtual int age() const override { return m_age; };
  virtual int weight() const override { return m_weight; };

 private:
  const int m_age, m_weight;
};

// Class Dog extends Animal interface
class Dog : public Animal {
 public:
  Dog(int age, int weight) : m_age{age}, m_weight{weight} {};

  // We have to override all the pure virtual methods of the base class (Animal)
  virtual std::string MakeNoise() const override { return "WOF WOF!"; };
  virtual int age() const override { return m_age; };
  virtual int weight() const override { return m_weight; };

 private:
  const int m_age, m_weight;
};

// Takes a pointer to the base object Animal
// returns a report about the animal
std::string MakeDoctorReport(const Animal::Ptr& animal) {
  std::stringstream ss;
  ss << "an animal age: " << animal->age() << ", weight: " << animal->weight()
     << " sounds like: " << animal->MakeNoise();
  return ss.str();
}

TEST(polymorphism_showcase, animals) {
  Animal::Ptr aDog = std::make_unique<Dog>(2, 8);
  Animal::Ptr aCat = std::make_unique<Cat>(3, 4);

  ASSERT_STREQ(MakeDoctorReport(aDog).c_str(),
               "an animal age: 2, weight: 8 sounds like: WOF WOF!");
  ASSERT_STREQ(MakeDoctorReport(aCat).c_str(),
               "an animal age: 3, weight: 4 sounds like: meow");
}