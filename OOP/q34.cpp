class Entity {
public:
    Entity(int age) : _age(age) {}
};

void process_entity(Entity e) {}

int main() {
    // Without explicit, this compiles and works!
    // The compiler silently converts the int 25 into an Entity(25).
    // This is often called "magic" and can be dangerous.
    process_entity(25);
}