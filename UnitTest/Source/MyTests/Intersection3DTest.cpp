#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#define GLM_FORCE_SILENT_WARNINGS
#define GLM_FORCE_XYZW_ONLY

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>


#include "libmath/Intersection3D.h"

#include <iostream>

TEST_CASE("Intersection3D", "[all][intersection]")
{
	SECTION("AABB")
	{
		mth::AABBCollider3D		controlAABB({ 4.f, 6.f, 1.f }, { 1.f, 3.f, 2.f });

		// Constructor / destructor
		{
			mth::AABBCollider3D		discard;
			mth::AABBCollider3D		copy = controlAABB;


			mth::Vector3			position{ 4.f, 6.f, 1.f }, extents{ 1.f, 3.f, 2.f };

			// Accessor
			CHECK(copy.GetMax() == controlAABB.GetPosition() + controlAABB.GetExtents());
			CHECK(copy.GetMin() == controlAABB.GetPosition() - controlAABB.GetExtents());

			CHECK(copy.GetPosition() == position);
			CHECK(copy.Position() == position);

			CHECK(copy.Extents() == extents);
			CHECK(copy.GetExtents() == extents);
		}

		SECTION("AABB / AABB")
		{

			mth::AABBCollider3D		noCollide({ 10.f, 8.f, 10.f }, { 1.f, 3.f, 1.f });
			mth::AABBCollider3D		collide({ 3.f, 7.f ,2.f }, { 3.1f, 1.f, 4.f });


			// Should not collide
			CHECK_FALSE(controlAABB.CheckCollision(noCollide));
			CHECK_FALSE(controlAABB.CheckCollision(mth::AABBCollider3D()));


			// Should collide with itself
			CHECK(controlAABB.CheckCollision(controlAABB));

			// Should collide
			CHECK(collide.CheckCollision(controlAABB));
		}

		SECTION("AABB / Sphere")
		{
			mth::SphereCollider3D	noCollide({ 3.1f, 15.f, 15.f }, 3.f);
			mth::SphereCollider3D	collide({ 4.3f, 1.f, 2.f }, 10.f);


			CHECK_FALSE(controlAABB.CheckCollision(noCollide));
			CHECK_FALSE(controlAABB.CheckCollision(mth::SphereCollider3D()));

			CHECK(controlAABB.CheckCollision(collide));
		}

	}


}