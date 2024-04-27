/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#
File Name:  main.cpp
Purpose:  Testing functionality for Geometric Algebra math library
Language: C++ / Eng, MSVC (used, but should work with most compilers)
Platform: MSVC / Windows 10 (used, but should have no requirements)
Project:  a.Surprise_CS393
Author:   Ari Surprise, a.surprise, 40000218
Creation date:  Spring 2023
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
#^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "Math/GP301.h"
#include "Math/Plane301.h"
#include "Math/Line301.h"
#include "Math/Point301.h"

int main()
{
  time_t now = std::chrono::system_clock::now().time_since_epoch().count();
  srand((u4)time(&now));
  f4 range = 64.0f;
  f4 hRange = range * AHALF;
  f4 div = InvF(static_cast<f4>(RAND_MAX) / range);
  dp::Plane301 p, o;
  dp::Point301 q, r;
  dp::Line301 t, s;
  dp::GP301 unit, product, lh, rh;
  constexpr u4 tests = 10;
  bool irreg = false;
  std::cout << std::boolalpha;
  for (s4 i = 0; i < 0; ++i)
  {
    p.Set((rand() * div) - hRange, (rand() * div) - hRange,
      (rand() * div) - hRange, (rand() * div) - hRange);
    o = p.Inverse();
    product = o * p;
    if (product != unit)
    {
      std::cout << i << ": " << o << " * " << p << " = " << product << "\n";
      if (!NearF(product.r, unit.r))
      {
        std::cout << "real: " << product.r << " != " << unit.r << std::endl;
      }
      if (!NearF(product.e23, unit.e23))
      {
        std::cout << "e23: " << product.e23 << " != " << unit.e23 << std::endl;
      }
      if (!NearF(product.e31, unit.e31))
      {
        std::cout << "e31: " << product.e31 << " != " << unit.e31 << std::endl;
      }
      if (!NearF(product.e12, unit.e12))
      {
        std::cout << "e12: " << product.e12 << " != " << unit.e12 << std::endl;
      }
      if (!NearF(product.e01, unit.e01))
      {
        std::cout << "e01: " << product.e01 << " != " << unit.e01 << std::endl;
      }
      if (!NearF(product.e02, unit.e02))
      {
        std::cout << "e02: " << product.e02 << " != " << unit.e02 << std::endl;
      }
      if (!NearF(product.e03, unit.e03))
      {
        std::cout << "e03: " << product.e03 << " != " << unit.e03 << std::endl;
      }
      if (!NearF(product.e0123, unit.e0123))
      {
        std::cout << "e0123: " << product.e0123 << " != " << unit.e0123 << "\n";
      }
      irreg = true;
    }
  }
  if (!irreg) { std::cout << "all Plane * Inverse products == 1\n"; }
  irreg = false;
  for (s4 i = 0; i < tests; ++i)
  {
    lh.Set
    (
      (rand() * div) - hRange,
      (rand() * div) - hRange, (rand() * div) - hRange, (rand() * div) - hRange,
      (rand() * div) - hRange, (rand() * div) - hRange, (rand() * div) - hRange,
      (rand() * div) - hRange
    );
    rh = lh.Inverse();
    product = lh * rh;
    if (product != unit)
    {
      std::cout << i << ": " << lh << " * " << rh << " = " << product << "\n";
      if (!NearF(product.r, unit.r))
      {
        std::cout << "real: " << product.r << " != " << unit.r << std::endl;
      }
      if (!NearF(product.e23, unit.e23))
      {
        std::cout << "e23: " << product.e23 << " != " << unit.e23 << std::endl;
      }
      if (!NearF(product.e31, unit.e31))
      {
        std::cout << "e31: " << product.e31 << " != " << unit.e31 << std::endl;
      }
      if (!NearF(product.e12, unit.e12))
      {
        std::cout << "e12: " << product.e12 << " != " << unit.e12 << std::endl;
      }
      if (!NearF(product.e01, unit.e01))
      {
        std::cout << "e01: " << product.e01 << " != " << unit.e01 << std::endl;
      }
      if (!NearF(product.e02, unit.e02))
      {
        std::cout << "e02: " << product.e02 << " != " << unit.e02 << std::endl;
      }
      if (!NearF(product.e03, unit.e03))
      {
        std::cout << "e03: " << product.e03 << " != " << unit.e03 << std::endl;
      }
      if (!NearF(product.e0123, unit.e0123))
      {
        std::cout << "e0123: " << product.e0123 << " != " << unit.e0123 << "\n";
      }
      irreg = true;
    }
  }
  if (!irreg) { std::cout << "all GP * Inverse products == 1\n"; }
  irreg = false;
  for (s4 i = 0; i < 0; ++i)
  {
    q.Set((rand() * div) - hRange, (rand() * div) - hRange,
      (rand() * div) - hRange, (rand() * div) - hRange);
    r = q.Inverse();
    product = r * q;
    if (product != unit)
    {
      std::cout << i << ": " << q << " * " << r << " = " << product << "\n";
      if (!NearF(product.r, unit.r))
      {
        std::cout << "real: " << product.r << " != " << unit.r << std::endl;
      }
      if (!NearF(product.e23, unit.e23))
      {
        std::cout << "e23: " << product.e23 << " != " << unit.e23 << std::endl;
      }
      if (!NearF(product.e31, unit.e31))
      {
        std::cout << "e31: " << product.e31 << " != " << unit.e31 << std::endl;
      }
      if (!NearF(product.e12, unit.e12))
      {
        std::cout << "e12: " << product.e12 << " != " << unit.e12 << std::endl;
      }
      if (!NearF(product.e01, unit.e01))
      {
        std::cout << "e01: " << product.e01 << " != " << unit.e01 << std::endl;
      }
      if (!NearF(product.e02, unit.e02))
      {
        std::cout << "e02: " << product.e02 << " != " << unit.e02 << std::endl;
      }
      if (!NearF(product.e03, unit.e03))
      {
        std::cout << "e03: " << product.e03 << " != " << unit.e03 << std::endl;
      }
      if (!NearF(product.e0123, unit.e0123))
      {
        std::cout << "e0123: " << product.e0123 << " != " << unit.e0123 << "\n";
      }
      irreg = true;
    }
  }
  if (!irreg) { std::cout << "all Point * Inverse products == 1\n"; }
  irreg = false;
  for (s4 i = 0; i < 0; ++i)
  {
    t.Set((rand() * div) - hRange, (rand() * div) - hRange,
      (rand() * div) - hRange, (rand() * div) - hRange,
      (rand() * div) - hRange, (rand() * div) - hRange);
    s = t.Inverse();
    product = t * s;
    if (product != unit)
    {
      std::cout << i << ": " << t << " * " << s << " = " << product << "\n";
      if (!NearF(product.r, unit.r))
      {
        std::cout << "real: " << product.r << " != " << unit.r << std::endl;
      }
      if (!NearF(product.e23, unit.e23))
      {
        std::cout << "e23: " << product.e23 << " != " << unit.e23 << std::endl;
      }
      if (!NearF(product.e31, unit.e31))
      {
        std::cout << "e31: " << product.e31 << " != " << unit.e31 << std::endl;
      }
      if (!NearF(product.e12, unit.e12))
      {
        std::cout << "e12: " << product.e12 << " != " << unit.e12 << std::endl;
      }
      if (!NearF(product.e01, unit.e01))
      {
        std::cout << "e01: " << product.e01 << " != " << unit.e01 << std::endl;
      }
      if (!NearF(product.e02, unit.e02))
      {
        std::cout << "e02: " << product.e02 << " != " << unit.e02 << std::endl;
      }
      if (!NearF(product.e03, unit.e03))
      {
        std::cout << "e03: " << product.e03 << " != " << unit.e03 << std::endl;
      }
      if (!NearF(product.e0123, unit.e0123))
      {
        std::cout << "e0123: " << product.e0123 << " != " << unit.e0123 << "\n";
      }
      irreg = true;
    }
  }
  if (!irreg) { std::cout << "all Line * Inverse products == 1\n"; }
  system("PAUSE");
  return 0;
}
