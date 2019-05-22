#pragma once
#define ROBOT_VERSION 0x020000
#define ROBOT_VERSION_STR "2.0.0"
#if defined(__linux__)
#define ROBOT_OS_LINUX
#if defined(__x86_64__)
#define ROBOT_ARCH_64
#else
#define ROBOT_ARCH_32
#endif
#elif defined(__APPLE__) && defined(__MACH__)
#define ROBOT_OS_MAC
#if defined(__x86_64__)
#define ROBOT_ARCH_64
#else
#define ROBOT_ARCH_32
#endif
#elif defined(_WIN32)
#define ROBOT_OS_WIN
#if defined(_WIN64)
#define ROBOT_ARCH_64
#else
#define ROBOT_ARCH_32
#endif
#else
#error We're sorry, your operating system is not supported.
#endif
#if defined(BUILDING_ROBOT_SHARED) && defined(USING_ROBOT_SHARED)
#error Please check your build configuration. Error detected.
#endif
#ifdef ROBOT_OS_WIN
#if defined(BUILDING_ROBOT_SHARED)
#define ROBOT_EXPORT __declspec(dllexport)
#elif defined(USING_ROBOT_SHARED)
#define ROBOT_EXPORT __declspec(dllimport)
#else
#define ROBOT_EXPORT
#endif
#elif (__GNUC__ >= 4)
#define ROBOT_EXPORT __attribute__((visibility("default")))
#else
#define ROBOT_EXPORT
#endif
#ifndef ROBOT_NS
#define ROBOT_NS Robot
#endif
#ifdef ROBOT_NS
#define ROBOT_NS_BEGIN \
    namespace ROBOT_NS \
    {
#define ROBOT_NS_END }
#define ROBOT_NS_PRE(name) ROBOT_NS::name
#define ROBOT_NS_FWD(name) \
    ROBOT_NS_BEGIN         \
    class name;            \
    ROBOT_NS_END
#define ROBOT_NS_USE_ALL using namespace ROBOT_NS;
#define ROBOT_NS_USE(name) using ROBOT_NS::name;
#else
#error This library must be encapsulated in a namespace
#endif
ROBOT_NS_BEGIN
typedef signed char int8;
typedef signed short int16;
typedef signed int int32;
typedef signed long long int64;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;
typedef float real32;
typedef double real64;
#ifdef ROBOT_ARCH_64
typedef int64 intptr;
typedef uint64 uintptr;
#else
typedef int32 intptr;
typedef uint32 uintptr;
#endif ROBOT_NS_END