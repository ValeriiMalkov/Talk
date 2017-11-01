#include "Barrier.h"
Barrier::Barrier() {}
Barrier::Barrier(const Barrier& barrier)
{
	this->road_ = barrier.road_;
	this->barrier_ = barrier.barrier_;
	this->object_ = barrier.object_;
	this->size_ = barrier.size_;
	this->X_ = barrier.X_;
	this->Y_ = barrier.Y_;
}
Barrier& Barrier::operator=(const Barrier& barrier)
{
	if (this != &barrier)
	{
		this->road_ = barrier.road_;
		this->barrier_ = barrier.barrier_;
		this->object_ = barrier.object_;
		this->size_ = barrier.size_;
		this->X_ = barrier.X_;
		this->Y_ = barrier.Y_;
		return *this;
	}
	else return *this;
}
Barrier::Barrier(Road & road) :size_(2),
object_(static_cast<char>(219)), Y_(0)
{
	road_ = &road;
	X_ = rand() % 23 + 1;
	while (true)
	{
		try
		{
			barrier_ = new char*[size_];
			for (int i = 0; i < size_; i++)
				barrier_[i] = new char[size_];
			return;
		}
		catch (bad_alloc)
		{

		}
	}

}
Barrier::~Barrier()
{
	barrierCleaner();
	for (int i = 0; i < size_; i++)
		delete[] barrier_[i];
	road_ = nullptr;
}
void Barrier::barrierInitializer()
{
	for (int i = 0; i < size_; ++i)
	{
		for (int j = 0; j < size_; ++j)
		{
			barrier_[i][j] = object_;
		}
	}
}
void Barrier::barrierCleaner()
{
	for (int i = 0; i < size_; ++i)
	{
		for (int j = 0; j < size_; ++j)
		{
			barrier_[i][j] = ' ';
		}
	}
	road_->setObject(X_, Y_, barrier_, size_);
}
void Barrier::goToRoad()
{
	barrierInitializer();
	road_->setObject(X_, Y_, barrier_, size_);
}
void Barrier::view()
{
	for (int i = 0; i < size_; ++i)
	{
		for (int j = 0; j < size_; ++j)
		{
			cout << barrier_[i][j];
		}
		cout << '\n';
	}
}
bool Barrier::newPosition()
{
	if ((Y_ + 2) >= road_->getSize())return false;
	else
	{
		barrierCleaner();
		Y_++;
		goToRoad();
		return true;
	}
}
char Barrier::getObject()
{
	return object_;
}