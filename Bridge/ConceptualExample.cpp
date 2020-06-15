// ===========================================================================
// ConceptualExample.cpp // Bridge Pattern
// ===========================================================================

#include <iostream>
#include <memory>

/**
 * The Implementor defines the interface for all implementation classes. It
 * doesn't have to match the Abstraction's interface. In fact, the two
 * interfaces can be entirely different. Typically the Implementor interface
 * provides only primitive operations, while the Abstraction defines higher-
 * level operations based on those primitives.
 */

class Implementor {
public:
    virtual ~Implementor() {}
    virtual std::string OperationImplementation() const = 0;
};

/**
 * Each Concrete Implementation corresponds to a specific platform and
 * implements the Implementor interface using that platform's API.
 */
class ConcreteImplementationA : public Implementor {
public:
    std::string OperationImplementation() const override {
        return "ConcreteImplementationA: Here's the result on the platform A.\n";
    }
};

class ConcreteImplementationB : public Implementor {
public:
    std::string OperationImplementation() const override {
        return "ConcreteImplementationB: Here's the result on the platform B.\n";
    }
};

/**
 * The Abstraction defines the interface for the "control" part of the two class
 * hierarchies. It maintains a reference to an object of the Implementor
 * hierarchy and delegates all of the real work to this object.
 */

class Abstraction {
protected:
    std::shared_ptr<Implementor> m_implementor;

public:
    Abstraction(std::shared_ptr<Implementor> implementor) : m_implementor(implementor) {
    }

    virtual ~Abstraction() {}

    virtual std::string Operation() const {
        return "Abstraction: Base operation with:\n" +
            m_implementor->OperationImplementation();
    }
};

/**
 * You can extend the Abstraction without changing the Implementor classes.
 */
class ExtendedAbstraction : public Abstraction {
public:
    ExtendedAbstraction(std::shared_ptr<Implementor> implementor) : Abstraction(implementor) {
    }
    std::string Operation() const override {
        return "ExtendedAbstraction: Extended operation with:\n" +
            m_implementor->OperationImplementation();
    }
};

/**
 * Except for the initialization phase, where an Abstraction object gets linked
 * with a specific Implementor object, the client code should only depend on
 * the Abstraction class. This way the client code can support any abstraction-
 * implementation combination.
 */
void clientCode(std::shared_ptr<Abstraction> abstraction) {
    // ...
    std::cout << abstraction->Operation();
    // ...
}

/**
 * The client code should be able to work with any pre-configured abstraction-
 * implementation combination.
 */
void test_conceptual_example() {

    std::shared_ptr<Implementor> implementor = std::make_shared<ConcreteImplementationA>();
    std::shared_ptr<Abstraction> abstraction = std::make_shared<Abstraction>(implementor);
    clientCode(abstraction);
    std::cout << std::endl;


    implementor = std::make_shared<ConcreteImplementationB>();
    abstraction = std::make_shared<ExtendedAbstraction>(implementor);
    clientCode(abstraction);
}

// ===========================================================================
// End-of-File
// ===========================================================================
