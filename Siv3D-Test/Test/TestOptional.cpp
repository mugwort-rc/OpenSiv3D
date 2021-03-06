﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "Siv3DTest.hpp"

# if defined(SIV3D_DO_TEST)

TEST(Optional, null)
{

}

TEST(Optional, ref)
{
	int i = 42;
	s3d::Optional<int&> opt{ i };
	EXPECT_EQ(&*opt, &i);
	EXPECT_EQ(&(opt.value()), &i);
	EXPECT_EQ(43, opt.then([](int&v) {return v = 43; }).value());
	EXPECT_EQ(*opt, 43);
	EXPECT_EQ(i, 43);
}

# endif
