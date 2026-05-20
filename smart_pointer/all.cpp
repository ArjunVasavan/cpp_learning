#include <iostream>
#include <memory>

// ─────────────────────────────────────────
// 1. Resource Class
// ─────────────────────────────────────────
class Resource {
private:
    int id;
public:
    Resource(int val) : id(val) {
        std::cout << "Resource " << id << " created" << std::endl;
    }
    ~Resource() {
        std::cout << "Resource " << id << " destroyed" << std::endl;
    }
    void use() {
        std::cout << "Resource " << id << " is being used" << std::endl;
    }
    int getId() const { return id; }
};

// ─────────────────────────────────────────
// 2. unique_ptr — Ownership Transfer
// ─────────────────────────────────────────
void processResource(std::unique_ptr<Resource> ptr) {
    std::cout << "\n[processResource] Ownership received." << std::endl;
    ptr->use();
    std::cout << "[processResource] Function ending — Resource will be destroyed here." << std::endl;
    // ptr goes out of scope → destructor fires automatically
}

int main() {

    std::cout << "════════════════════════════════" << std::endl;
    std::cout << "   unique_ptr DEMO              " << std::endl;
    std::cout << "════════════════════════════════" << std::endl;

    std::unique_ptr<Resource> uptr = std::make_unique<Resource>(1);
    uptr->use();

    // ❌ This would FAIL — copy is deleted
    // std::unique_ptr<Resource> uptr2 = uptr;

    // ✅ Transfer ownership using move
    std::cout << "\nTransferring ownership via std::move..." << std::endl;
    processResource(std::move(uptr));

    // uptr is now null — dangerous to use
    if (!uptr) {
        std::cout << "uptr is now null after move." << std::endl;
    }

    // ─────────────────────────────────────────
    // 3. shared_ptr — Shared Ownership
    // ─────────────────────────────────────────
    std::cout << "\n════════════════════════════════" << std::endl;
    std::cout << "   shared_ptr DEMO              " << std::endl;
    std::cout << "════════════════════════════════" << std::endl;

    std::shared_ptr<Resource> sptr1 = std::make_shared<Resource>(2);
    std::cout << "use_count after sptr1 created : " << sptr1.use_count() << std::endl; // 1

    {
        std::shared_ptr<Resource> sptr2 = sptr1; // both point to same object
        std::cout << "use_count after sptr2 created : " << sptr1.use_count() << std::endl; // 2
        sptr2->use();

        std::cout << "Resetting sptr2..." << std::endl;
        sptr2.reset(); // sptr2 releases ownership
        std::cout << "use_count after sptr2 reset   : " << sptr1.use_count() << std::endl; // 1
    } // sptr2 already reset, no effect here

    std::cout << "use_count before sptr1 reset  : " << sptr1.use_count() << std::endl; // 1
    sptr1.reset(); // last owner releases → destructor fires
    std::cout << "use_count after sptr1 reset   : " << sptr1.use_count() << std::endl; // 0

    // ─────────────────────────────────────────
    // 4. weak_ptr — Non-Owning Observer
    // ─────────────────────────────────────────
    std::cout << "\n════════════════════════════════" << std::endl;
    std::cout << "   weak_ptr DEMO                " << std::endl;
    std::cout << "════════════════════════════════" << std::endl;

    std::weak_ptr<Resource> wptr;

    {
        std::shared_ptr<Resource> sptr3 = std::make_shared<Resource>(3);
        wptr = sptr3; // weak_ptr observes but does NOT increase use_count

        std::cout << "use_count (shared): " << sptr3.use_count() << std::endl; // 1
        std::cout << "wptr expired?       " << wptr.expired() << std::endl;    // 0 (false)

        // Access safely via lock()
        if (auto locked = wptr.lock()) { // lock() returns a shared_ptr
            std::cout << "Accessed via lock(): ";
            locked->use();
            std::cout << "use_count inside lock: " << locked.use_count() << std::endl; // 2
        }

        std::cout << "\nsptr3 going out of scope..." << std::endl;
    } // sptr3 destroyed here → Resource 3 destroyed

    // wptr now dangles — expired() returns true
    std::cout << "wptr expired after sptr3 gone? " << wptr.expired() << std::endl; // 1 (true)

    if (auto locked = wptr.lock()) {
        locked->use(); // Never reaches here
    } else {
        std::cout << "lock() returned null — object already destroyed." << std::endl;
    }

    // ─────────────────────────────────────────
    // BONUS: Shared Pointer Cycle (Memory Leak)
    // ─────────────────────────────────────────
    std::cout << "\n════════════════════════════════" << std::endl;
    std::cout << "   BONUS: Cycle DEMO            " << std::endl;
    std::cout << "════════════════════════════════" << std::endl;

    struct Node {
        int val;
        std::shared_ptr<Node> next; // ❌ causes cycle if two nodes point to each other
        // std::weak_ptr<Node> next; // ✅ fix: use weak_ptr to break the cycle
        ~Node() { std::cout << "Node " << val << " destroyed" << std::endl; }
    };

    {
        auto A = std::make_shared<Node>(Node{1});
        auto B = std::make_shared<Node>(Node{2});

        A->next = B;
        // B->next = A; // ❌ Uncomment this to create a cycle → neither A nor B destroyed!
        
        std::cout << "A use_count: " << A.use_count() << std::endl;
        std::cout << "B use_count: " << B.use_count() << std::endl;
    } // Without cycle: both destroyed cleanly here

    std::cout << "\nMain ending." << std::endl;
    return 0;
}
