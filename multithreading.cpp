#include <random> // for random number generating
#include <iomanip> // used for setprecision
#include <iostream>

#include <thread> // library to create threads
#include <mutex>
int getRandomWorkTime(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(250, 500);
    return dist(gen);

}



int piesPerBaker=5;
int piesBaked=0;
int noOfBakers=4;
std::mutex mtx; 
int piesNeeded=20;

void baker(int id){
    for (int i=0; i<piesPerBaker; i++){
        int workTime=0;
        {
            std::lock_guard<std::mutex> lock(mtx);
            workTime=getRandomWorkTime();
            if (piesBaked==piesNeeded) return;
            std::cout << "...Baker" << id << " is making pie #" << (piesBaked + 1) << std::endl;
            piesBaked++;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(workTime));
    }
}
int main(){
auto start=std::chrono::steady_clock::now();

 // Create and run 8 bakers(threads)
 std::thread baker1(baker, 1);
 std::thread baker2(baker, 2);
 std::thread baker3(baker, 3);
 std::thread baker4(baker, 4);
 std::thread baker5(baker, 5);
 std::thread baker6(baker, 6);
 std::thread baker7(baker, 7);
 std::thread baker8(baker, 8);
 
 // Main thread will wait for all bakers(threads) to return before continuing
 baker1.join();
 baker2.join();
 baker3.join();
 baker4.join();
 baker5.join();
 baker6.join();
 baker7.join();
 baker8.join();

auto end=std::chrono::steady_clock::now();
 std::chrono::duration<double> elapsed=end-start;
 std::cout << "\nResults\n   Total pies baked: " << piesBaked << "/" << (piesPerBaker * noOfBakers) << std::endl;
std::cout<<std::setprecision(2)<<"   total tyime: "<<elapsed.count()<<"s"<<std::endl;

system("pause");
return 0;
}
