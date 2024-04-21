#pragma once

namespace mystl {

string::string(size_type count, value_type ch) {
	// 1. 申请空间
	iterator xpos = Alloc::allocate(count);
	// 2. 填充元素
}

void string::init_space(size_type size) {
	try	{
		begin_ = Alloc::allocate(size);
		end_ = begin_ + size;
		cap_ = begin_ + size;
	}
	catch(...)	{
		begin_ = nullptr;
		end_ = nullptr;
		cap_ = nullptr;
		throw;
	}
	
}

}