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

# include <Siv3D/Fwd.hpp>
# include <Siv3D/Geometry2D.hpp>
# include <Siv3D/PointVector.hpp>
# include <Siv3D/Line.hpp>
# include <Siv3D/Circle.hpp>
# include <Siv3D/Rectangle.hpp>
# include <Siv3D/Triangle.hpp>

namespace s3d
{
	namespace detail
	{
		//
		//	http://stackoverflow.com/questions/849211/shortest-distance-between-a-point-and-a-line-segment
		//
		static double DistanceSq(const Vec2& begin, const Vec2& end, const Vec2& p) noexcept
		{
			const double l2 = begin.distanceFromSq(end);

			if (l2 == 0.0)
			{
				return begin.distanceFromSq(p);
			}

			const double t = std::max(0.0, std::min(1.0, (p - begin).dot(end - begin) / l2));

			const Vec2 projection = begin + t * (end - begin);

			return p.distanceFromSq(projection);
		}
	}

	namespace Geometry2D
	{
		bool Intersect(const Point& a, const Point& b) noexcept
		{
			return a == b;
		}

		bool Intersect(const Point& a, const Vec2& b) noexcept
		{
			return b.distanceFromSq(a) < 1.0;
		}

		bool Intersect(const Point& a, const Line& b) noexcept
		{
			return detail::DistanceSq(b.begin, b.end, a) < 1.0;
		}

		bool Intersect(const Point& a, const Rect& b) noexcept
		{
			return b.x <= a.x && a.x < (b.x + b.w) && b.y <= a.y && a.y < (b.y + b.h);
		}

		bool Intersect(const Point& a, const RectF& b) noexcept
		{
			return b.x <= a.x && a.x < (b.x + b.w) && b.y <= a.y && a.y < (b.y + b.h);
		}

		bool Intersect(const Point& a, const Circle& b) noexcept
		{
			return a.distanceFromSq(b.center) <= (b.r * b.r);
		}





		bool Intersect(const Vec2& a, const Circle& b) noexcept
		{
			return a.distanceFromSq(b.center) <= (b.r * b.r);
		}



		bool Intersect(const Line& a, const Circle& b) noexcept
		{
			const Vec2 ab = a.end - a.begin;
			const Vec2 ac = b.center - a.begin;
			const Vec2 bc = b.center - a.end;
			const double e = ac.dot(ab);
			const double rr = b.r * b.r;

			if (e <= 0.0)
			{
				return ac.dot(ac) <= rr;
			}

			const double f = ab.dot(ab);

			if (e >= f)
			{
				return bc.dot(bc) <= rr;
			}

			return (ac.dot(ac) - e * e / f) <= rr;
		}






		bool Intersect(const Rect& a, const Circle& b) noexcept
		{
			const double aw = a.w * 0.5;
			const double ah = a.h * 0.5;
			const double cX = std::abs(b.x - a.x - aw);
			const double cY = std::abs(b.y - a.y - ah);

			if (cX > (aw + b.r) || cY > (ah + b.r))
			{
				return false;
			}

			if (cX <= (aw) || cY <= (ah))
			{
				return true;
			}

			return (cX - aw) * (cX - aw) + (cY - ah) * (cY - ah) <= (b.r * b.r);
		}

		bool Intersect(const Circle& a, const Point& b) noexcept
		{
			return Intersect(b, a);
		}

		bool Intersect(const Circle& a, const Vec2& b) noexcept
		{
			return Intersect(b, a);
		}
	}
}