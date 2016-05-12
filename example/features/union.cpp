
#include <boost/contract.hpp>
#include <boost/config.hpp>
#include <cassert>
    
#ifdef BOOST_GCC // G++ does not support static union members yet.
    int instances_ = 0;
#endif

//[union
union positive {
    static void static_invariant() {
        BOOST_CONTRACT_ASSERT(instances() >= 0);
    }
    
    void invariant() const {
        BOOST_CONTRACT_ASSERT(i_ > 0);
        BOOST_CONTRACT_ASSERT(d_ > 0);
    }

    explicit positive(int x) {
        // Unions cannot have bases so ctor preconditions here.
        boost::contract::constructor_precondition<positive> pre([&] {
            BOOST_CONTRACT_ASSERT(x > 0);
        });
        boost::contract::old_ptr<int> old_instances =
                BOOST_CONTRACT_OLDOF(instances());
        boost::contract::guard c = boost::contract::constructor(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(instances() == *old_instances + 1);
            })
        ;

        i_ = x;
        ++instances_;
    }
    
    explicit positive(double x) {
        // Unions cannot have bases so ctor preconditions here.
        boost::contract::constructor_precondition<positive> pre([&] {
            BOOST_CONTRACT_ASSERT(x > 0);
        });
        boost::contract::old_ptr<int> old_instances =
                BOOST_CONTRACT_OLDOF(instances());
        boost::contract::guard c = boost::contract::constructor(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(instances() == *old_instances + 1);
            })
        ;

        d_ = x;
        ++instances_;
    }

    ~positive() {
        boost::contract::old_ptr<int> old_instances =
                BOOST_CONTRACT_OLDOF(instances());
        boost::contract::guard c = boost::contract::destructor(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(instances() == *old_instances - 1);
            })
        ;

        --instances_;
    }

    void get(int& x) {
        boost::contract::guard c = boost::contract::public_function(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(x > 0);
            });
        ;
        
        x = i_;
    }
    
    void get(double& x) {
        boost::contract::guard c = boost::contract::public_function(this)
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(x > 0);
            });
        ;
        
        x = d_;
    }

    static int instances() {
        boost::contract::guard c = boost::contract::public_function<positive>();
        return instances_;
    }

private:
    int i_;
    double d_;
    
    /* ... */
//]
    #ifndef BOOST_GCC // G++ does not support static union members yet.
        static int instances_;
    #endif
};

#ifndef BOOST_GCC // G++ does not support static union members yet.
    int positive::instances_ = 0;
#endif

int main() {
    {
        int i = -456;
        positive p(123);
        assert(p.instances() == 1);
        p.get(i);
        assert(i == 123);

        double d = -4.56;
        positive q(1.23);
        assert(q.instances() == 2);
        q.get(d);
        assert(d == 1.23);
    }
    assert(positive::instances() == 0);
    return 0;
}

