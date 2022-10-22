#pragma once

namespace Engine {
	class LinkedList
	{
	public:
		LinkedList() :mNext(nullptr)
		{
		}

		virtual void PushBack(LinkedList* node) 
		{
			if (mNext == nullptr)
			{
				mNext = node;
			}
			else 
			{
				if (mNext == node)
				{
					return;
				}
				Next<LinkedList>()->PushBack(node);
			}
		}

		virtual void Remove(LinkedList* node) 
		{
			if (mNext != nullptr)
			{
				if (node == mNext)
				{
					mNext = node->Next<LinkedList>();
					node->mNext = nullptr;
				}
				else 
				{
					Next<LinkedList>()->Remove(node);
				}
			}
		}

	protected:
		LinkedList * mNext;

		template<typename T>
		T* Next() 
		{
			return (T*)mNext;
		}
	};

	class DoubleLinkedList {
	public:
		DoubleLinkedList(): mPrev(nullptr), mNext(nullptr) {}

		void Append(DoubleLinkedList* node) 
		{
			if (mNext != nullptr)
			{
				mNext->Append(node);
			}
			else 
			{
				mNext = node;
				node->mPrev = this;
			}
		}

		void Remove(DoubleLinkedList* node) 
		{
			if (mNext != nullptr && mNext != node)
			{
				mNext->Remove(node);
			}
		}

		void Clear() 
		{
			if (mPrev != nullptr)
			{
				mPrev->mNext = mNext;
			}
			if (mNext != nullptr)
			{
				mNext->mPrev = mPrev;
			}
			mPrev = nullptr;
			mNext = nullptr;
		}

	protected:
		DoubleLinkedList* mPrev;
		DoubleLinkedList* mNext;

		template<typename T>
		T* Next() 
		{
			return (T*)mNext;
		}

		template<typename T>
		T* Prev()
		{
			return (T*)mPrev;
		}
	};
}

