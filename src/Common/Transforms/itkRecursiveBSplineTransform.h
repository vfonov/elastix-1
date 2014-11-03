/*======================================================================

  This file is part of the elastix software.

  Copyright (c) University Medical Center Utrecht. All rights reserved.
  See src/CopyrightElastix.txt or http://elastix.isi.uu.nl/legal.php for
  details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE. See the above copyright notices for more information.

======================================================================*/
#ifndef __itkRecursiveBSplineTransform_h
#define __itkRecursiveBSplineTransform_h

#include "itkAdvancedBSplineDeformableTransform.h"

#include "itkRecursiveBSplineInterpolationWeightFunction.h"


namespace itk
{
/** \class RecursiveBSplineTransform
 * \brief A recursive implementation of a B-spline deformable transform
 *
 * The class is templated coordinate representation type (float or double),
 * the space dimension and the spline order.
 *
 * \ingroup ITKTransform
 * \wikiexample{Registration/ImageRegistrationMethodBSpline,
 *   A global registration of two images}
 */

template< typename TScalarType = double,
  unsigned int NDimensions = 3,
  unsigned int VSplineOrder = 3 >
class RecursiveBSplineTransform :
  public AdvancedBSplineDeformableTransform< TScalarType, NDimensions, VSplineOrder >
{
public:
  /** Standard class typedefs. */
  typedef RecursiveBSplineTransform              Self;
    typedef AdvancedBSplineDeformableTransform<
      TScalarType, NDimensions, VSplineOrder >   Superclass;
  typedef SmartPointer<Self>                     Pointer;
  typedef SmartPointer<const Self>               ConstPointer;

  /** New macro for creation of through the object factory. */
  itkNewMacro( Self );

  /** Run-time type information (and related methods). */
  itkTypeMacro( RecursiveBSplineTransform, AdvancedBSplineDeformableTransform );

  /** Dimension of the domain space. */
  itkStaticConstMacro( SpaceDimension, unsigned int, NDimensions );

  /** The BSpline order. */
  itkStaticConstMacro( SplineOrder, unsigned int, VSplineOrder );

  /** Standard scalar type for this class. */
  typedef typename Superclass::ScalarType             ScalarType;
  typedef typename Superclass::ParametersType         ParametersType;
  typedef typename Superclass::ParametersValueType    ParametersValueType;
  typedef typename Superclass::NumberOfParametersType NumberOfParametersType;
  typedef typename Superclass::JacobianType           JacobianType;
  typedef typename Superclass::InputVectorType        InputVectorType;
  typedef typename Superclass::OutputVectorType       OutputVectorType;
  typedef typename Superclass::InputCovariantVectorType  InputCovariantVectorType;
  typedef typename Superclass::OutputCovariantVectorType OutputCovariantVectorType;
  typedef typename Superclass::InputVnlVectorType     InputVnlVectorType;
  typedef typename Superclass::OutputVnlVectorType    OutputVnlVectorType;
  typedef typename Superclass::InputPointType         InputPointType;
  typedef typename Superclass::OutputPointType        OutputPointType;

  /** Parameters as SpaceDimension number of images. */
  typedef typename Superclass::PixelType             PixelType;
  typedef typename Superclass::ImageType             ImageType;
  typedef typename Superclass::ImagePointer          ImagePointer;
  //typedef typename Superclass::CoefficientImageArray CoefficientImageArray;

  /** Typedefs for specifying the extend to the grid. */
  typedef typename Superclass::RegionType     RegionType;
  typedef typename Superclass::IndexType      IndexType;
  typedef typename Superclass::SizeType       SizeType;
  typedef typename Superclass::SpacingType    SpacingType;
  typedef typename Superclass::DirectionType  DirectionType;
  typedef typename Superclass::OriginType     OriginType;
  typedef typename Superclass::GridOffsetType GridOffsetType;
  typedef typename GridOffsetType::OffsetValueType  OffsetValueType;

  typedef typename Superclass::NonZeroJacobianIndicesType     NonZeroJacobianIndicesType;
  typedef typename Superclass::SpatialJacobianType            SpatialJacobianType;
  typedef typename Superclass::JacobianOfSpatialJacobianType  JacobianOfSpatialJacobianType;
  typedef typename Superclass::SpatialHessianType             SpatialHessianType;
  typedef typename Superclass::JacobianOfSpatialHessianType   JacobianOfSpatialHessianType;
  typedef typename Superclass::InternalMatrixType             InternalMatrixType;

  /** Interpolation weights function type. */
  typedef typename Superclass::WeightsFunctionType                WeightsFunctionType;
  typedef typename Superclass::WeightsFunctionPointer             WeightsFunctionPointer;
  typedef typename Superclass::WeightsType                        WeightsType;
  typedef typename Superclass::ContinuousIndexType                ContinuousIndexType;
  typedef typename Superclass::DerivativeWeightsFunctionType      DerivativeWeightsFunctionType;
  typedef typename Superclass::DerivativeWeightsFunctionPointer   DerivativeWeightsFunctionPointer;
  typedef typename Superclass::SODerivativeWeightsFunctionType    SODerivativeWeightsFunctionType;
  typedef typename Superclass::SODerivativeWeightsFunctionPointer SODerivativeWeightsFunctionPointer;

  /** Parameter index array type. */
  typedef typename Superclass::ParameterIndexArrayType ParameterIndexArrayType;

  typedef itk::RecursiveBSplineInterpolationWeightFunction<
    TScalarType, NDimensions, VSplineOrder >                      RecursiveBSplineWeightFunctionType;

  /** Compute point transformation. This one is commonly used.
   * It calls RecursiveBSplineTransformImplementation2::InterpolateTransformPoint
   * for a recursive implementation.
   */
  virtual OutputPointType TransformPoint( const InputPointType & point ) const;

  /** Compute point transformation. Calls the five-argument version, which uses
   * RecursiveBSplineTransformImplementation::InterpolateTransformPoint
   * for a less smart recursive implementation.
   */
  virtual OutputPointType TransformPointOld( const InputPointType & point ) const;
  virtual void TransformPoint( const InputPointType & inputPoint, OutputPointType & outputPoint,
    WeightsType & weights, ParameterIndexArrayType & indices, bool & inside ) const;

  /** Compute the Jacobian of the transformation. */
  virtual void GetJacobian(
    const InputPointType & ipp,
    JacobianType & j,
    NonZeroJacobianIndicesType & nzji ) const;

  /** Compute the spatial Jacobian of the transformation. */
  virtual void GetSpatialJacobian(
    const InputPointType & ipp,
    SpatialJacobianType & sj ) const;

protected:

  RecursiveBSplineTransform();
  virtual ~RecursiveBSplineTransform(){};

  typedef typename Superclass::JacobianImageType JacobianImageType;
  typedef typename Superclass::JacobianPixelType JacobianPixelType;

  typename RecursiveBSplineWeightFunctionType::Pointer m_RecursiveBSplineWeightFunction;

  virtual void ComputeNonZeroJacobianIndices(
    NonZeroJacobianIndicesType & nonZeroJacobianIndices,
    const RegionType & supportRegion ) const;

private:

  RecursiveBSplineTransform( const Self & ); // purposely not implemented
  void operator=( const Self & );            // purposely not implemented

}; // end class RecursiveBSplineTransform





/** Helper class that implements recursive B-spline interpolation of the transformation. */
template< unsigned int SpaceDimension, unsigned int SplineOrder, class TScalar >
class RecursiveBSplineTransformImplementation
{
public:
  itkStaticConstMacro( HelperConstVariable, unsigned int,
    ( SpaceDimension - 1 ) * ( SplineOrder + 1 ) );

  /** TransformPoint recursive implementation. */
  static inline TScalar InterpolateTransformPoint(
    const TScalar * mu, const long * steps, const double * weights1D,
    const TScalar * coefBasePointer, Array<unsigned long> & indices, unsigned int & c )
  {
    TScalar coord = 0.0;
    for( unsigned int k = 0; k <= SplineOrder; ++k )
    {
      const TScalar * tmp_mu = mu + steps[ k + HelperConstVariable ];
      coord += RecursiveBSplineTransformImplementation< SpaceDimension - 1, SplineOrder, TScalar >
        ::InterpolateTransformPoint( tmp_mu, steps, weights1D, coefBasePointer, indices, c ) * weights1D[ k + HelperConstVariable ];
	}
    return coord;
  } // end InterpolateTransformPoint()


  /** GetJacobian recursive implementation. */
  static inline void InterpolateGetJacobian(
    TScalar * & jacobians, const double * weights1D , double value )
  {
    for( unsigned int k = 0; k <= SplineOrder; ++k )
    {
      RecursiveBSplineTransformImplementation< SpaceDimension - 1, SplineOrder, TScalar >
        ::InterpolateGetJacobian( jacobians, weights1D, value * weights1D[ k + HelperConstVariable ] );
    }
  } // end InterpolateGetJacobian()


  /** SpatialJacobian recursive implementation. */
  static inline void InterpolateSpatialJacobian(
    TScalar derivativeAndValue[],
    const TScalar * mu,
    const long * steps,
    const double * weights,
    const double * derivativeWeights )
  {
    /** derivativeAndValue length must be at least dim + 1. */
    TScalar derivativeAndValueNext[ SpaceDimension + 1 ];
    for( unsigned int n = 0; n <= SpaceDimension; ++n )
    {
      derivativeAndValue[ n ] = 0.0;
    }

    for( unsigned int k = 0; k <= SplineOrder; ++k )
    {
      const TScalar * tmp_mu = mu + steps[ k + HelperConstVariable ];

      RecursiveBSplineTransformImplementation< SpaceDimension - 1, SplineOrder, TScalar >::
        InterpolateSpatialJacobian( derivativeAndValueNext, tmp_mu, steps, weights, derivativeWeights );
      for( unsigned int n = 0; n < SpaceDimension; ++n )
      {
        derivativeAndValue[ n ] += derivativeAndValueNext[ n ] * weights[ k + HelperConstVariable ];
      }
      derivativeAndValue[ SpaceDimension ]
        += derivativeAndValueNext[ 0 ] * derivativeWeights[ k + HelperConstVariable ];
    }
  } // end InterpolateSpatialJacobian()

}; // end class


/** Helper class that implements recursive B-spline interpolation of the transformation. */
template< unsigned int OutputDimension, unsigned int SpaceDimension, unsigned int SplineOrder, class TScalar >
class RecursiveBSplineTransformImplementation2
{
public:

  itkStaticConstMacro( HelperConstVariable, unsigned int,
    ( SpaceDimension - 1 ) * ( SplineOrder + 1 ) );

  typedef itk::RecursiveBSplineInterpolationWeightFunction<
    TScalar, OutputDimension, SplineOrder >            RecursiveBSplineWeightFunctionType;
  itkStaticConstMacro( BSplineNumberOfIndices, unsigned int,
    RecursiveBSplineWeightFunctionType::NumberOfIndices );

  typedef TScalar *  OutputPointType;
  typedef TScalar ** CoefficientPointerVectorType;

  /** TransformPoint recursive implementation. */
  static inline void TransformPoint(
    OutputPointType opp,
    const CoefficientPointerVectorType mu, const OffsetValueType * steps, const double * weights1D )
  {
    TScalar * tmp_mu[ OutputDimension ];
    TScalar tmp_opp[ OutputDimension ];
    for( unsigned int k = 0; k <= SplineOrder; ++k )
    {
      for( unsigned int j = 0; j < OutputDimension; ++j )
      {
        tmp_opp[ j ] = 0.0;
        tmp_mu[ j ] = mu[ j ] + steps[ k + HelperConstVariable ];
      }

      RecursiveBSplineTransformImplementation2< OutputDimension, SpaceDimension - 1, SplineOrder, TScalar >
        ::TransformPoint( tmp_opp, tmp_mu, steps, weights1D );
      for( unsigned int j = 0; j < OutputDimension; ++j )
      {
        opp[ j ] += tmp_opp[ j ] * weights1D[ k + HelperConstVariable ];
      }
    }
  } // end TransformPoint()


  /** TransformPoint recursive implementation. */
  static inline void TransformPoint2(
    OutputPointType opp, const CoefficientPointerVectorType mu,
    const OffsetValueType * bsplineOffsetTable,
    const double * weights1D )
  {
    TScalar * tmp_mu[ OutputDimension ];
    for( unsigned int j = 0; j < OutputDimension; ++j )
    {
      tmp_mu[ j ] = mu[ j ];
    }

    TScalar tmp_opp[ OutputDimension ];
    OffsetValueType bot = bsplineOffsetTable[ SpaceDimension - 1 ];
    for( unsigned int k = 0; k <= SplineOrder; ++k )
    {
      for( unsigned int j = 0; j < OutputDimension; ++j )
      {
        tmp_opp[ j ] = 0.0;
      }

      RecursiveBSplineTransformImplementation2< OutputDimension, SpaceDimension - 1, SplineOrder, TScalar >
        ::TransformPoint2( tmp_opp, tmp_mu, bsplineOffsetTable, weights1D );
      for( unsigned int j = 0; j < OutputDimension; ++j )
      {
        opp[ j ] += tmp_opp[ j ] * weights1D[ k + HelperConstVariable ];
        tmp_mu[ j ] += bot;
      }
    }
  } // end TransformPoint()


  /** ComputeNonZeroJacobianIndices recursive implementation. */
  static inline void RecursiveComputeNonZeroJacobianIndices(
    unsigned long * nzji,
    unsigned long parametersPerDim,
    unsigned long currentIndex,
    const OffsetValueType * gridOffsetTable,
    unsigned int & c )
  {
    OffsetValueType bot = gridOffsetTable[ SpaceDimension - 1 ];
    for( unsigned int k = 0; k <= SplineOrder; ++k )
    {
      RecursiveBSplineTransformImplementation2< OutputDimension, SpaceDimension - 1, SplineOrder, TScalar >
        ::RecursiveComputeNonZeroJacobianIndices( nzji, parametersPerDim, currentIndex, gridOffsetTable, c );
      currentIndex += bot;
    }
  } // end RecursiveComputeNonZeroJacobianIndices()


}; // end class


/**  ******************************************************************
 * End cases of the functions.
 * A pointer to the coefficients is returned.
 */

template< unsigned int SplineOrder, class TScalar >
class RecursiveBSplineTransformImplementation< 0, SplineOrder, TScalar >
{
public:

  /** TransformPoint recursive implementation. */
  static inline TScalar InterpolateTransformPoint(
    const TScalar * mu,
    const long * steps,
    const double * weights1D,
    const TScalar *coefBasePointer,
    Array<unsigned long> & indices,// nodig voor de jacobian, want dit is de nzji
    unsigned int & c )
  {
    indices[ c ] = mu - coefBasePointer;
    ++c;
    return *mu;
  } // end InterpolateTransformPoint()


  /** GetJacobian recursive implementation. */
  // outerdim template parameter nodig
  static inline void InterpolateGetJacobian(
    TScalar * & jacobians, const double * weights1D, double value )
  {
    *jacobians = value;//*dm/dx
	  //for( i = outerdim){ jacobians[64*i ] = value * dmdx[i]}
  	++jacobians;
  } // end InterpolateGetJacobian()


  /** SpatialJacobian recursive implementation. */
  static inline void InterpolateSpatialJacobian(
    TScalar derivativeAndValue[],
    const TScalar * mu,
    const long * steps,
    const double * weights,
    const double * derivativeWeights )
  {
    derivativeAndValue[ 0 ] = *mu;
  } // end InterpolateSpatialJacobian()

}; // end class


template< unsigned int OutputDimension, unsigned int SplineOrder, class TScalar >
class RecursiveBSplineTransformImplementation2< OutputDimension, 0, SplineOrder, TScalar >
{
public:

  typedef itk::RecursiveBSplineInterpolationWeightFunction<
    TScalar, OutputDimension, SplineOrder >            RecursiveBSplineWeightFunctionType;
  itkStaticConstMacro( BSplineNumberOfIndices, unsigned int,
    RecursiveBSplineWeightFunctionType::NumberOfIndices );

  typedef TScalar *  OutputPointType;
  typedef TScalar ** CoefficientPointerVectorType;

  /** TransformPoint recursive implementation. */
  static inline void TransformPoint(
    OutputPointType opp,
    const CoefficientPointerVectorType mu, const OffsetValueType * steps, const double * weights1D )
  {
    for( unsigned int j = 0; j < OutputDimension; ++j )
    {
      opp[ j ] = *(mu[ j ]);
    }

  } // end TransformPoint()

  /** TransformPoint recursive implementation. */
  static inline void TransformPoint2(
    OutputPointType opp, const CoefficientPointerVectorType mu,
    const OffsetValueType * bsplineOffsetTable,
    const double * weights1D )
  {
    for( unsigned int j = 0; j < OutputDimension; ++j )
    {
      opp[ j ] = *(mu[ j ]);
    }
  } // end TransformPoint()


  /** ComputeNonZeroJacobianIndices recursive implementation. */
  static inline void RecursiveComputeNonZeroJacobianIndices(
    unsigned long * nzji,
    unsigned long parametersPerDim,
    unsigned long currentIndex,
    const OffsetValueType * gridOffsetTable,
    unsigned int & c )
  {
    for( unsigned int j = 0; j < OutputDimension; ++j )
    {
      nzji[ c + j * BSplineNumberOfIndices ] = currentIndex + j * parametersPerDim;
    }
    ++c;
  } // end RecursiveComputeNonZeroJacobianIndices()

}; // end class


} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkRecursiveBSplineTransform.hxx"
#endif

#endif /* __itkRecursiveBSplineTransform_h */
