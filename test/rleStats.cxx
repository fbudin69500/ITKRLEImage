/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#include "itkTestDriverIncludeRequiredIOFactories.h"
#include "itkRLEImage.h"
#include "itkImageFileReader.h"
#include <string>
#include <iostream>

int main( int argc, char* argv[] )
{
  if( argc < 2 )
    {
    std::cerr << "Usage: " << argv[0] << " inputImage" << std::endl;
    return EXIT_FAILURE;
    }

  typedef itk::Image<short, 3>    ImageType;
  typedef itk::RLEImage<short, 3> myRLEImage;

  typedef itk::ImageFileReader < ImageType > ReaderType;
  typename ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName(argv[1]);

  typedef itk::RegionOfInterestImageFilter<ImageType, myRLEImage> inConverterType;
  typename inConverterType::Pointer inConv = inConverterType::New();

  try
    {
    RegisterRequiredFactories();
    reader->Update();
    inConv->SetInput(reader->GetOutput());
    inConv->SetRegionOfInterest(reader->GetOutput()->GetLargestPossibleRegion());
    inConv->Update();
    typename myRLEImage::Pointer test = inConv->GetOutput();
    std::cout << test;
    }
  catch( itk::ExceptionObject & error )
    {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
    }
  return EXIT_SUCCESS;
}
