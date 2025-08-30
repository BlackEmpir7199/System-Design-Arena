#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// the oberserver iterface
class ISubscriber
{
public:
    virtual void update() = 0;
    virtual ~ISubscriber() = default;
};

// the observable interface
class IChannel
{
public:
    virtual void attach(ISubscriber *subscriber) = 0;
    virtual void detach(ISubscriber *subscriber) = 0;
    virtual void notifyAll() = 0;
    virtual ~IChannel() = default;
};

// the concrete observable
class Channel : public IChannel {
    private:
        string name;
        string latestVideo;
        vector<ISubscriber*> subscribers;
    public:
        Channel(string name) : name(name){} 

        // attach func
        void attach(ISubscriber* sub) override{
            if(find(subscribers.begin(),subscribers.end(),sub)==subscribers.end())
                subscribers.push_back(sub);
        }

        // detach func
        void detach(ISubscriber* sub) override{
            auto it = find(subscribers.begin(),subscribers.end(),sub);
            if(it != subscribers.end())
                subscribers.erase(it);
        }

        // notify all func
        void notifyAll() override{
            // notifies the observable has been updated 
            for(ISubscriber* sub: subscribers){
                // this is not a push method
                sub->update();
            }
        }   
        
        // upload video which changes the observable state
        void uploadVideo(string title){
            latestVideo = title;
            cout << "Notification : " << name << endl;
            cout << "New Video uploaded: " << title << endl;
            notifyAll();
        }

        // returns the current change of the observable
        string getInfo(){
            return latestVideo;
        }

        string getName(){ return name; }
};


// the concrete observer
class Subscriber : public ISubscriber
{
    private:
        string name;
        Channel* channel;
    public:
        Subscriber(string name, Channel* channel) : name(name) , channel(channel){}

        // pull model
        void update() override{
            cout << "Hi, " << name << " "<< channel->getName() << " Has dropped a new video , " << channel->getInfo() << endl;
        }
};



int main()
{
    Channel* channel = new Channel("Codehub");

    Subscriber* sub1 = new Subscriber("Manith",channel);
    Subscriber* sub2 = new Subscriber("Vineeth",channel);

    channel->attach(sub1);
    channel->attach(sub2);

    channel->uploadVideo("Crack MAANG in 1 day");

    channel->detach(sub2);

    channel->uploadVideo("How to fool people in 1 day");

    return 0;
}