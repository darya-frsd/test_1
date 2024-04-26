#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include <cassert>

struct Student {
    int id;
    std::string name;
    int age;
};

class StudentDatabase {
private:
    std::map<int, std::shared_ptr<Student>> database;

public:
    void addStudent(int id, const std::string& name, int age) {
        assert(id > 0);
        assert(age > 0);
        assert(name != "");
        assert(database.find(id) == database.end());

        auto new_student = std::make_shared<Student>(Student{id, name, age});
        database[id] = new_student;
    }

    void removeStudent(int id) {
        assert(id > 0);
        assert(database.find(id) != database.end());

        database.erase(id);
    }

    std::shared_ptr<Student> getStudent(int id) {
        assert(id > 0);
        auto it = database.find(id);
        if (it != database.end()) {
            return it->second;
        }
        return nullptr;
    }
};

int main() {
    StudentDatabase db;

    // test addStudent
    db.addStudent(1, "Alice", 20);
    db.addStudent(2, "Bob", 21);

    // test getStudent
    assert(db.getStudent(1)->name == "Alice");
    assert(db.getStudent(2)->age == 21);

    // test removeStudent
    db.removeStudent(1);
    assert(db.getStudent(1) == nullptr);
    
    std::cout << "All tests passed!" << std::endl;

    return 0;
}
