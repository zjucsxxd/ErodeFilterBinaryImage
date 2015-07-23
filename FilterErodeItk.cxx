//BinaryErodeImageFilter

#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include <iostream>

#include "itkBinaryErodeImageFilter.h"
#include "itkBinaryBallStructuringElement.h"

int main(int argc, char *argv[])
{
  if(argc<2)
    {
     std::cout << "3 arguments required : InputImage + OutputImage + radius"<<std::endl;
     return EXIT_FAILURE;
    }

  unsigned int radius = 2;
  if (argc>2)
    {
      radius = atoi(argv[3]);
    }

  // Image Type
  typedef itk::Image<unsigned char, 2> ImageType;
  //Read Image
  typedef itk::ImageFileReader<ImageType> ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName(argv[1]);
  reader->Update() ;

  //Write Image
  typedef itk::ImageFileWriter< ImageType > WriterType ;
  WriterType::Pointer writer = WriterType::New();

  //Define structuring element
  const unsigned int Dimension = 2;
  typedef unsigned char InputPixelType;
  typedef itk::BinaryBallStructuringElement< InputPixelType, Dimension > StructuringElementType;
  StructuringElementType structuringElement;
  structuringElement.SetRadius(radius);
  structuringElement.CreateStructuringElement();

  //Define erode filter
  typedef itk::BinaryErodeImageFilter <ImageType, ImageType,  StructuringElementType> BinaryErodeImageFilterType;
  BinaryErodeImageFilterType::Pointer erodeFilter = BinaryErodeImageFilterType::New();
  erodeFilter->SetInput(reader->GetOutput());
  erodeFilter->SetKernel(structuringElement);

  writer->SetInput( erodeFilter->GetOutput() ) ;
  writer->SetFileName( argv[2]) ;
  writer->Update() ;
  return EXIT_SUCCESS;

}
