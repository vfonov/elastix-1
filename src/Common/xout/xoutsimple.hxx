#ifndef __xoutsimple_hxx
#define __xoutsimple_hxx

#include "xoutsimple.h"

namespace xoutlibrary
{
	using namespace std;


	/**
	 * ********************* Constructor ****************************
	 */

	template< class charT, class traits >
		xoutsimple<charT, traits>::xoutsimple()
	{
		//nothing

	} // end Constructor


	/**
	 * ********************* Destructor *****************************
	 */

	template< class charT, class traits >
		xoutsimple<charT, traits>::~xoutsimple()
	{
		//nothing

	} // end Destructor


	/**
	 * **************** AddOutput (ostream_type) ********************
	 */

	template< class charT, class traits >
		int xoutsimple<charT, traits>::
		AddOutput( const char * name, ostream_type * output )
	{
		return this->AddTargetCell( name, output );
		
	} // end AddOutput


	/**
	 * **************** AddOutput (xoutsimple) **********************
	 */

	template< class charT, class traits >
		int xoutsimple<charT, traits>::
		AddOutput( const char * name, Superclass * output )
	{
		return this->AddTargetCell( name, output );

	} // end AddOutput


	/**
	 * ***************** RemoveOutput *******************************
	 */

	template< class charT, class traits >
		int xoutsimple<charT, traits>::
		RemoveOutput( const char * name )
	{
		return this->RemoveTargetCell( name );

	} // end RemoveOutput


	/**
	 * **************** SetOutputs (ostream_types) ******************
	 */

	template< class charT, class traits >
		void xoutsimple<charT, traits>::
		SetOutputs( const CStreamMapType & outputmap )
	{		
		this->SetTargetCells( outputmap );

	} // end SetOutputs

	
	/**
	 * **************** SetOutputs (xoutobjects) ********************
	 */

	template< class charT, class traits >
		void xoutsimple<charT, traits>::
		SetOutputs( const XStreamMapType & outputmap )
	{		
		this->SetTargetCells( outputmap );

	} // end SetOutputs
	

	/**
	 * **************** GetOutputs (map of xoutobjects) *************
	 */

	template< class charT, class traits >
		const typename xoutbase<charT, traits>::XStreamMapType &
		xoutsimple<charT, traits>::GetXOutputs(void)
	{		
		return this->m_XTargetCells;

	} // end GetOutputs

	
	/**
	 * **************** GetOutputs (map of c-streams) ***************
	 */

	template< class charT, class traits >
		const typename xoutbase<charT, traits>::CStreamMapType &
		xoutsimple<charT, traits>::GetCOutputs(void)
	{		
		return this->m_CTargetCells;

	} // end GetOutputs


} // end namespace xoutlibrary


#endif // end #ifndef __xoutsimple_hxx

