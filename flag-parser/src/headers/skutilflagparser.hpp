#pragma once
#ifndef _SKUTIL_FLAG_PARSER_HPP
#define _SKUTIL_FLAG_PARSER_HPP

#include <vector>
#include <array>
#include <iostream>
#include <functional>
#include <cstring>

namespace SKUTIL
{
	#ifndef SKUTIL_VECTOR
		template<typename T>
		using SK_VEC = std::vector<T>;
	#endif

	#ifndef SKUTIL_FLAG_TYPES
		using SHORT_FLAG = char;
		using LONG_FLAG = const char*;

		constexpr const char* SHORT_FLAG_DELIM {"-"};
		constexpr const char* LONG_FLAG_DELIM {"--"};

 		#define OPT [[maybe_unused]]
	#endif 

    // Do keep in mind that count represents the amount of values that the flag
    // expects, for now it is hardcoded to only accept 1 value since my library
    // does not support functionality for multiple values
    //
    // Type information about the value will also be handled by the user in this
    // function since each flag might ask for a different type such as a string,
    // int, double, ect...
	#ifndef SKUTIL_FLAG_PARAM_LIST
		typedef void (*skutils_flag_param_func_)(int count, ...);
	#endif

	/*
	 * Remove any nullptr values from a char buffer
	 *
	 * @param initCount (int): initial count of values that [buf] contains
	 * @param buf (char**): buffer to check for nullptrs
	 * @param outBuf(char**): Output buffer
	 *
	 * @returns: NONE
	 */  
	inline void RemoveNullStrs(int initCount, char** buf, char*** outBuf)
	{
		auto nullptrCount = [&]() -> int {
			int count = 0;
			
			for (int i = 0; i < initCount; i++) {
				if (buf[i] == nullptr)
					count++;	
			}

			return count;
		};

		// Set the size of the output buffer to the [buf] size minus the amount of nullptrs found
		int outBufSize = initCount - nullptrCount();
		*outBuf = new char*[outBufSize];
		// std::cout << "Nullptr Count - " << nullptrCount() << std::endl;
		// return;

		for (int idx = 0, c = 0; c < outBufSize; idx++) {
			if (buf[idx] != nullptr) {
				*outBuf[c] = buf[idx];
				c++;
			}
		}
	}

	struct Flag
	{
		SHORT_FLAG mShortIdentifier;
		LONG_FLAG mLongIdentifier;
		const char* mDescription;
		OPT skutils_flag_param_func_ mFunction;

		bool operator==(const Flag& other)
		{
			if (mShortIdentifier == other.mShortIdentifier ||
				std::strcmp(mLongIdentifier, other.mLongIdentifier) == 0)
				return true;

			return false;
		}

		bool operator!=(const Flag& other)
		{
			if (mShortIdentifier != other.mShortIdentifier &&
				std::strcmp(mLongIdentifier, other.mLongIdentifier) != 0)
				return true;

			return false;
		}
	};

	#ifndef STRUTIL_NULL_FLAG
		constexpr Flag NULL_FLAG = {' ', "", "", nullptr};
	#endif 

	class FlagParser
	{
		public:
			SK_VEC<Flag>* mAllFlags;
			SK_VEC<Flag>* mSetFlags;

			FlagParser(SK_VEC<Flag>* _flags)
			{
				mAllFlags = _flags;

				// Check if any flags passed were reserved
				CheckForReserved();

				// After all custom flags have been added
				// append the reserve flags to mAllFlags
				for (size_t flagIdx = 0; flagIdx < RESV.size(); flagIdx++) {
					mAllFlags->push_back(RESV[flagIdx]);
				}
			}

			void ParseFlags(int argc, char** argv) 
			{
				int flagCount = 0;
				for (int i = 1; i < argc; i++) {
					Flag f = NULL_FLAG;
					if (std::strncmp(argv[i], LONG_FLAG_DELIM, 2) == 0) {
						char* arg = new char[sizeof(argv[i]) - 2];

						// Strip the delimiter
						size_t idx = 0;
						while (idx <= sizeof(arg)) {
							arg[idx] = argv[i][idx + 2];
							idx++;
						}

						FindFlag(NULL_FLAG.mShortIdentifier, arg, &f);
					} else if (std::strncmp(argv[i], SHORT_FLAG_DELIM, 1) == 0) {
						// Strip the delimiter
						SHORT_FLAG arg = (char)(*(argv[i] + 1));
						FindFlag(arg, NULL_FLAG.mLongIdentifier, &f);
					}

					// If the flag is not null call its function
					if (f == NULL_FLAG)
						continue;

                    // IMPORTANT
                    // right now, each flag assums only one argument will be passed
                    // which means only one value can be associated to each flag and
                    // cannot be specified otherwise, for example
                    //
                    // ./[app-name] -a 1 <- This works since flag 'a' only accepts value [1]
                    // ./[app-name] -a 1 2 <- Does not work since flag 'a' is followed by [1] and [2]
                    //
                    // I would like to add this as a feature in the future to make the flag
                    // parse more useful in a variety of use cases
                    constexpr int ACCEPTABLE_FLAG_VALUE_COUNT {1};
					f.mFunction(ACCEPTABLE_FLAG_VALUE_COUNT);
					argv[i] = nullptr;
					flagCount++;
				}

				char** tmp = nullptr;
				RemoveNullStrs(argc, argv, &tmp);
			}

			~FlagParser()
			{
				
			}

		private:
            static void ShowHelp(OPT int count, ...)
            {
                std::cout << "Help\n";
            }

			SK_VEC<Flag> RESV = SK_VEC<Flag> {
				NULL_FLAG,
				{
					'h',
					"help",
					"Show help commands",
				    ShowHelp
				},
			};

			// TODO: Optimize this method further
			void CheckForReserved()
			{
				if (mAllFlags->empty())
					return;

				bool remove;
				// size_t index;
				for (Flag res : RESV) {
					remove = false;
					for (size_t i = 0; i < mAllFlags->size(); i++) {
						if (res.mShortIdentifier == mAllFlags->at(i).mShortIdentifier ||
							res.mLongIdentifier == mAllFlags->at(i).mLongIdentifier) {
							std::cerr << "Flag Was already reserved: " << "Short -> " << res.mShortIdentifier << std::endl;
							remove = true;
							// index = i;
						}
					}

					if (remove) {
						// mFlags->erase(index);
					}
				}
			}

			void FindFlag(OPT SHORT_FLAG shorthand, OPT LONG_FLAG longhand, Flag* outFlag)
			{
				*outFlag = NULL_FLAG;
				if (shorthand == NULL_FLAG.mShortIdentifier && 
					std::strcmp(longhand, NULL_FLAG.mLongIdentifier) == 0)
					return;


				for (Flag f : *mAllFlags) {
					if (shorthand == f.mShortIdentifier ||
						strcmp(longhand, f.mLongIdentifier) == 0) {
						*outFlag = f;
					}
				}	
			}

			bool FlagAlreadySet(const Flag& flag)
			{
				for (Flag f : *mSetFlags) {
					if (f.mShortIdentifier == flag.mShortIdentifier ||
						f.mLongIdentifier == flag.mLongIdentifier) {
						return true;
					}
				}

				return false;
			}
	};
}

// Remove all pre-processor macros that don't need to be defined for other programs
#undef SKUTIL_VECTOR 
#undef SKUTIL_FLAG_TYPES
#undef SKUTIL_FLAG_PARAM_LIST

#endif // _SKUTIL_FLAG_PARSER_HPP
