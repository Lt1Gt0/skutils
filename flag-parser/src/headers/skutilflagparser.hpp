#pragma once

#ifndef _SKUTIL_FLAG_PARSER_HPP
#define _SKUTIL_FLAG_PARSER_HPP

#include <vector>
#include <array>
#include <iostream>

namespace SKUTIL
{
	#ifndef SKUTIL_VECTOR
		template<typename T>
		using SK_VEC = std::vector<T>;
	#endif

	#ifndef SKUTIL_FLAG_TYPES
		using SHORT_FLAG = const char;
		using LONG_FLAG = const char*;

		constexpr const char SHORT_FLAG_DELIM {'-'};
		constexpr const char* LONG_FLAG_DELIM {"--"};
	#endif 


	struct Flag
	{
		SHORT_FLAG mShortIdentifier;
		LONG_FLAG mLongIdentifier;
		const char* mDescription;
	};

	class FlagParser
	{
		public:
			SK_VEC<Flag>* mFlags;

			FlagParser(SK_VEC<Flag>* _flags)
			{
				mFlags = nullptr;
				mFlags = _flags;

				CheckForReserved();
			}

			~FlagParser()
			{

			}

		private:
			SK_VEC<Flag> RESV = SK_VEC<Flag> {
				{
					'h',
					"help",
					"Show help commands"
				},
			};

			// TODO: Optimize this method further
			void CheckForReserved()
			{
				if (mFlags->empty())
					return;

				bool remove;
				size_t index;
				for (Flag res : RESV) {
					remove = false;
					for (size_t i = 0; i < mFlags->size(); i++) {
						if (res.mShortIdentifier == mFlags->at(i).mShortIdentifier ||
							res.mLongIdentifier == mFlags->at(i).mLongIdentifier) {
							std::cerr << "Flag Was already reserved: " << "Short -> " << res.mShortIdentifier << std::endl;
							remove = true;
							index = i;
						}
					}

					if (remove) {
						mFlags->erase(index);
					}
				}
			}
	};
}

// Remove all pre-processor macros that don't need to be defined for other programs
#undef SKUTIL_VECTOR 
#undef SKUTIL_FLAG_TYPES

#endif // _SKUTIL_FLAG_PARSER_HPP
