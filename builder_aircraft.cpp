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

	class ABuilder{
		protected:
		Aircraft* aircraft;
		public:
		virtual void createPlane() = 0;
		virtual void createHelicopter() = 0;
		
		virtual ~ABuilder(){};
		virtual Aircraft* getAircraft(){return aircraft;};
	};
	
	class rusBuilder: public ABuilder{
		public:

		virtual void createPlane() { aircraft = new RussianPlane();};
		virtual void createHelicopter(){aircraft = new RussianHelicopter();};
		
	};
	
	class usaBuilder: public ABuilder{
		public:

		virtual void createPlane() { aircraft = new AmericanPlane();};
		virtual void createHelicopter(){ aircraft = new AmericanHelicopter();};
	};
	
	class Customer{
		Aircraft *aircraft;
		public:
		void createPlane(ABuilder& builder){

			builder.createPlane();
			aircraft = builder.getAircraft();
		}
		
		void createHelicopter(ABuilder& builder){

			builder.createHelicopter();
			aircraft = builder.getAircraft();
		}
		Aircraft* getAircraft(){return aircraft;};
		
	};

	class AFactory{
		public:
		virtual Plane* createPlane() = 0;
		virtual Helicopter* createHelicopter() = 0;
		virtual ~AFactory(){};
	};
	
	class usaFactory: public AFactory{
		public:
		Plane* createPlane() override { 
			Customer customer;
			usaBuilder usa; 
			customer.createPlane(usa); 
			return static_cast<aviation::Plane*>(customer.getAircraft());
		};
		
		Helicopter* createHelicopter() override { 
			Customer customer;
			usaBuilder usa; 
			customer.createHelicopter(usa); 
			return static_cast<aviation::Helicopter*>(customer.getAircraft());
		};
	};
	
	class rusFactory: public AFactory{
		public:
		Plane* createPlane() override { return new RussianPlane();};
		Helicopter* createHelicopter() override { return new RussianHelicopter();};
	};
	
	class Creator{
		std::vector<Aircraft*> aircrafts;
		public:
		void info() {
			for(int i=0; i<aircrafts.size(); ++i) {
				aircrafts[i]->info();
			}
		}
		void add(Aircraft* aircraft){
			aircrafts.push_back(aircraft);
		};
		void deleteAll(){
			for(int i=0; i<aircrafts.size(); ++i) {
				delete aircrafts[i];
			}	
		};
			
	};
	
	
}	
int main(){
  
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

