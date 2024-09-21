#ifndef __BINDABLEEVENT_HPP__
#define __BINDABLEEVENT_HPP__

#include <vector>
#include <functional>
#include <algorithm>

template <typename Arg>
class BindableEvent
{
public:
	BindableEvent() = default;
	~BindableEvent() = default;

	class Connection
	{
	public:
		Connection() = default;

		Connection(std::function<void(Arg)> func, BindableEvent &event)
		{
			_func = func;
			_event = event;
		}

		void Disconnect()
		{
			_event._Connections.erase(std::find(
				_event._Connections.begin(),
				_event._Connections.end(),
				_func));
		}

		Connection& operator=(const Connection& a)		
		{
			_func = a._func; 
			_event = a._event; 
			return *this;
		}
	private:
		std::function<void(Arg)> _func;
		BindableEvent &_event;
	};

	Connection Connect(std::function<void(Arg)> func)
	{
		_Connections.push_back(Connection(func, this));
	}

	void Wait();

	void Fire(const Arg &args)
	{
		for (Connection i : _Connections)
		{
			i._func(args);
		}
	}

private:
	std::vector<Connection> _Connections;
};

#endif // __BINDABLEEVENT_HPP__


