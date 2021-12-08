#include <iostream>
#include <vector>

using namespace std;

namespace aviation {

    class Aircraft{
    public:
        virtual void info() = 0;
        virtual ~Aircraft(){};
    };

    class Plane: public Aircraft{
    public:
        void info() override {
            cout << "Plane class" << endl;
        }
    };

    class Helicopter: public Aircraft{
    public:
        void info() override {
            cout << "Helicopter class" << endl;
        }
    };

    class RussianPlane: public Plane{
    public:
        void info() override {
            cout << "it is russian plane" << endl;
        }
    };

    class RussianHelicopter: public Helicopter{
    public:
        void info() override {
            cout << "it is russian helicopter" << endl;
        }

    };

    class AmericanPlane: public Plane{
    public:
        void info() override {
            cout << "it is american plane" << endl;
        }
    };

    class AmericanHelicopter: public Helicopter{
    public:
        void info() override {
            cout << "it is american helicopter" << endl;
        }

    };

    class AFactory{
    public:
        virtual Plane* createPlane() = 0;
        virtual Helicopter* createHelicopter() = 0;
        virtual ~AFactory(){};
    };

    class usaFactory: public AFactory{
    public:
        Plane* createPlane() override { return new AmericanPlane();};
        Helicopter* createHelicopter() override { return new AmericanHelicopter();};
    };

    class rusFactory: public AFactory{
    public:
        Plane* createPlane() override { return new RussianPlane();};
        Helicopter* createHelicopter() override { return new RussianHelicopter();};
    };

    class Creator{
        std::vector<Aircraft*> units;
    public:
        void info() {
            for(int i=0; i<units.size(); ++i) {
                units[i]->info();
            }
        }
        void add(Aircraft* aircraft){
            units.push_back(aircraft);
        };
        void deleteAll(){
            for(int i=0; i<units.size(); ++i) {
                delete units[i];
            }
        };
    };
}

int main(){

    aviation::Plane plane;
    plane.info();

    aviation::rusFactory rus;
    aviation::usaFactory usa;
    aviation::Creator ivan, john;
    int N = 2;
    for (int i = 0; i < N; ++i){
        ivan.add(rus.createPlane());
        ivan.add(rus.createHelicopter());
        john.add(usa.createPlane());
        john.add(usa.createHelicopter());
    }
    
    ivan.info();

    john.info();

    ivan.deleteAll();
    john.deleteAll();
    return 0;
}
