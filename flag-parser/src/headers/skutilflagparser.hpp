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

	#ifndef SKUTIL_FLAG_PARAM_LIST
		typedef void (*skutils_flag_param_func_)(...);
	#endif


	struct Flag
	{
		SHORT_FLAG mShortIdentifier;
		LONG_FLAG mLongIdentifier;
		const char* mDescription;
		OPT skutils_flag_param_func_ mFunction;

		Flag& operator=(const Flag& other)
		{
			this->mShortIdentifier = other.mShortIdentifier;
			this->mLongIdentifier= other.mLongIdentifier;
			this->mDescription = other.mDescription;
			this->mFunction = other.mFunction;
			return *this;
		}

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
				CheckForReserved();
			}

			void ParseFlags(int argc, char** argv) 
			{
				for (int i = 0; i < argc; i++) {
					// std::cout << argv[i] << "\n";
					Flag f = {};
					if (std::strncmp(argv[i], LONG_FLAG_DELIM, 2) == 0) {
						char* arg = new char[sizeof(argv[i])];
						std::memcpy(arg, argv[i] + 2, sizeof(arg - 2));
						FindFlag(NULL_FLAG.mShortIdentifier, arg, &f);
					} else if (std::strncmp(argv[i], SHORT_FLAG_DELIM, 1) == 0) {
						SHORT_FLAG arg = (char)((*argv[i]) + 1);
						FindFlag(arg, NULL_FLAG.mLongIdentifier, &f);
					}

					// If the flag is not null call its function
					if (f != NULL_FLAG)
						f.mFunction();
				}
			}

			~FlagParser()
			{
				
			}

		private:
			SK_VEC<Flag> RESV = SK_VEC<Flag> {
				NULL_FLAG,
				{
					'h',
					"help",
					"Show help commands",
					nullptr
				},
			};

			// TODO: Optimize this method further
			void CheckForReserved()
			{
				if (mAllFlags->empty())
					return;

				bool remove;
				size_t index;
				for (Flag res : RESV) {
					remove = false;
					for (size_t i = 0; i < mAllFlags->size(); i++) {
						if (res.mShortIdentifier == mAllFlags->at(i).mShortIdentifier ||
							res.mLongIdentifier == mAllFlags->at(i).mLongIdentifier) {
							std::cerr << "Flag Was already reserved: " << "Short -> " << res.mShortIdentifier << std::endl;
							remove = true;
							index = i;
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
						longhand == f.mLongIdentifier) {
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
