#ifndef __MESSAGE_QUEUE_HPP__
#define __MESSAGE_QUEUE_HPP__

#include <queue>
#include <mutex>
#include <condition_variable>

template<class T>
class MessageQueue {
public:
	void push(const T &message) {
		std::lock_guard<std::mutex> lock(mutex_);
		queue_.push(message);
		cv_.notify_one();
	}

	bool poll(T &message) {
		bool ret = false;
		std::lock_guard<std::mutex> lock(mutex_);
		if (queue_.size()) {
			message = queue_.front();
			queue_.pop();
			ret = true;
		}
		return ret;
	}

	void wait(T &message) {
		std::unique_lock<std::mutex> lock(mutex_);
		while (!queue_.size()) {
			cv_.wait(lock);
		}
		message = queue_.front();
		queue_.pop();
	}

	std::cv_status wait_for(T &message, std::chrono::seconds timeOut) {
		std::cv_status status(std::cv_status::no_timeout);
		std::unique_lock<std::mutex> lock(mutex_);
		if (!queue_.size()) {
			status = cv_.wait_for(lock, timeOut);
		}

		if (std::cv_status::timeout != status) {
			message = queue_.front();
			queue_.pop();
		}
		return status;
	}

	size_t size(void) {
		std::lock_guard<std::mutex> lock(mutex_);
		return queue_.size();
	}

private:
	std::queue<T> queue_;
	std::mutex mutex_;
	std::condition_variable cv_;
};

#endif