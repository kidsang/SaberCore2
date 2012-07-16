/*
 * time: 2012/07/11
 * author: kid
 */

#include <queue>
#include <map>
#include <iostream>
#include <string>
#include <cassert>
#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>

using std::string;

struct scEvent
{
	string name;
	int value;
	//TODO:timestamp
};

typedef boost::shared_ptr<scEvent> scEventPtr;

class scEventRouter
{
	typedef std::deque<scEventPtr> EventQueue;
	typedef boost::shared_ptr<EventQueue> EventQueuePtr;
	typedef std::map<string, EventQueuePtr> QueueNameMap;
	/// ����ָʾ�����¼�Ӧ��ȥ���ĸ�outputQueue
	typedef std::map<string, string> EventMap;

public:
	//void createInputQueue(string const& name)
	//{
	//	boost::mutex::scoped_lock lock(mInputMutex);
	//	// ȷ����Ϣ���в��������ֳ�ͻ
	//	assert(mInputQueues.find(name) == mInputQueues.end());
	//	mInputQueues.insert(std::make_pair(name, EventQueuePtr(new EventQueue())));
	//}

	void createOutputQueue(string const& name)
	{
		boost::mutex::scoped_lock lock(mOutputMutex);
		// ȷ����Ϣ���в��������ֳ�ͻ
		assert(mOutputQueues.find(name) == mOutputQueues.end());
		mOutputQueues.insert(std::make_pair(name, EventQueuePtr(new EventQueue())));
	}

	void registerEvent(string const& evtName, string const& queName)
	{
		boost::mutex::scoped_lock lock(mOutputMutex);
		// ȷ����Ϣ���Ͳ��������ֳ�ͻ
		assert(mEventMap.find(evtName) == mEventMap.end());
		// ȷ����Ϣ���д���
		auto iter = mOutputQueues.find(queName);
		assert(iter != mOutputQueues.end());

		mEventMap.insert(std::make_pair(evtName, queName));
	}

	/// ���¼�put���������
	void putEvent(/*string const& queName, */scEventPtr const& evt)
	{
		boost::mutex::scoped_lock lock(mInputMutex);
		// ȷ����Ϣ���ʹ���
		assert(mEventMap.find(evt->name) != mEventMap.end());
		// ȷ����Ϣ���д���
		//auto iter = mInputQueues.find(queName);
		//assert(iter != mInputQueues.end());
		//iter->second->push_back(evt);
		mInputQueue.push_back(evt);
	}

	/// �����������fetch
	bool const fetchEvent(string const& queName, scEventPtr & evtOut)
	{
		boost::mutex::scoped_lock lock(mOutputMutex);
		// ȷ����Ϣ���д���
		auto iter = mOutputQueues.find(queName);
		assert(iter != mOutputQueues.end());

		if (iter->second->empty())
			return false;

		evtOut = iter->second->at(0);
		iter->second->pop_front();
		return true;
	}
	
	// ִ��·�ɹ���
	// ��ͣ�ش�input queue��fetch����put��output queue��
	void run()
	{
		while (true)
		{
			//for (auto input = mInputQueues.begin(); input != mInputQueues.end(); ++input)
			//{

				boost::mutex::scoped_lock inlock(mInputMutex);
				boost::mutex::scoped_lock outlock(mOutputMutex);
				//while (!input->second->empty())
				while (!mInputQueue.empty())
				{
					// �����������fetch
					//scEventPtr evt = input->second->at(0);
					//input->second->pop_front();
					scEventPtr evt = mInputQueue.at(0);
					mInputQueue.pop_front();
					// put����Ӧ�������
					string outname = mEventMap.find(evt->name)->second;
					auto output = mOutputQueues.find(outname);
					output->second->push_back(evt);

					std::cout << "transfer " << evt->name << " " << evt->value << std::endl;
					//std::cout << input->first << ": " << input->second->size() << std::endl;
					//std::cout << output->first << ": " << output->second->size() << std::endl;
				}
				/*
				if (!input->second->empty())
				{
					scEventPtr evt;
					{
						boost::mutex::scoped_lock lock(mInputMutex);
						// �����������fetch
						evt = input->second->at(0);
						input->second->pop_front();
						//std::cout << "transfer " << evt->name << " " << evt->value << std::endl;
						std::cout << input->first << ": " << input->second->size() << std::endl;
					}
					{
						boost::mutex::scoped_lock lock(mOutputMutex);
						// put����Ӧ�������
						string outname = mEventMap.find(evt->name)->second;
						auto output = mOutputQueues.find(outname);
						output->second->push_back(evt);
						std::cout << output->first << ": " << output->second->size() << std::endl;
					}
				}
				*/
			//}
		}
	}

private:
	//QueueNameMap mInputQueues;
	EventQueue mInputQueue;
	QueueNameMap mOutputQueues;
	EventMap mEventMap;

	boost::mutex mInputMutex;
	boost::mutex mOutputMutex;

};

void main()
{
	scEventRouter* r = new scEventRouter();

	boost::thread t1(
		[&]()
	{
		r->run();
	}
		);

	//r->createInputQueue("ClientInput");
	r->createOutputQueue("ClientOutput");
	//r->createInputQueue("ServerInput");
	r->createOutputQueue("ServerOutput");

	r->registerEvent("c2s", "ServerOutput");
	r->registerEvent("s2c", "ClientOutput");


	boost::thread t2(
		[&]()
	{
		for (int i=0; i<1000; ++i)
		{
			scEventPtr evt(new scEvent());
			evt->name = "c2s";
			evt->value = i;
			//r->putEvent("ClientInput", evt);
			r->putEvent(evt);
			r->fetchEvent("ClientOutput", evt);
		}
		scEventPtr evt(new scEvent());
		//while(1)
			//r->fetchEvent("ClientOutput", evt);
	}
	);

	boost::thread t3(
		[&]()
	{
		for (int i=0; i<1000; ++i)
		{
			scEventPtr evt(new scEvent());
			evt->name = "s2c";
			evt->value = i;
			//r->putEvent("ServerInput", evt);
			r->putEvent(evt);
			r->fetchEvent("ServerOutput", evt);
		}
		scEventPtr evt(new scEvent());
		//while(1)
			//r->fetchEvent("ServerOutput", evt);
	}
	);

	system("pause");
}