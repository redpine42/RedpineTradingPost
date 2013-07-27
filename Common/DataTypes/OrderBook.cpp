#include "OrderBook.h"
#include "L2Data.h"

OrderBook::OrderBook(std::string & symbol, DataEnums::OrderSide side)
	: symbol_(symbol),
	  side_(side)
{
}

OrderBook::~OrderBook()
{
    BookDataMapIter iter;
    for(iter = bookData_.begin(); iter != bookData_.end(); ++iter)
    {
		L2DataVec & bookData = (*iter).second;
		L2DataVecIter iter;
		for(iter = bookData.begin(); iter != bookData.end(); ++iter)
		{
			delete (*iter);
		}
    }
	bookData_.erase(bookData_.begin(), bookData_.end());

}

void OrderBook::addData(const L2Data * data)
{
	std::string mmid = data->MMID_;
	bookData_[mmid].push_back(data);
	if(data->size_ <= 0 || data->price_ <= 0.0)
	{
		L2DataVec & bookData = bookData_[mmid];
		L2DataVecIter iter;
		for(iter = bookData.begin(); iter != bookData.end(); ++iter)
		{
			delete (*iter);
		}
		bookData_.erase(mmid);
	}
}


