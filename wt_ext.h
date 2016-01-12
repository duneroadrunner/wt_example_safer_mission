#ifndef WT_EXT_H_
#define WT_EXT_H_

#include "mseregisteredforlegacy.h"

namespace Wt {

	template<class _Ty>
	class WWidgetPtr : public mse::TRegisteredPointerForLegacy<_Ty> {
	public:
		//using _Ty::_Ty;
		// the version of the compiler (msvc 2013) being used does not yet support inherited constructors, so we use this macro hack
		// for now
		MSE_USING(WWidgetPtr, mse::TRegisteredPointerForLegacy<_Ty>);
	};

	template<class _Ty, class... Args>
	WWidgetPtr<_Ty> WWidgetNew(Args&&... args) { return mse::registered_new_for_legacy<_Ty>(args...); }

	/* Presumably Wt::WWidgetDelete() will rarely be used as the Wt library generally takes ownership of WWidgets. */
	template <class _Ty>
	void WWidgetDelete(const WWidgetPtr<_Ty>& ptr_cref) { mse::registered_delete_for_legacy<_Ty>(ptr_cref); }

}

#endif // WT_EXT_H_
