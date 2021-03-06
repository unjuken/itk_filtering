#include "itkMeanImageFilter.h"
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

int
main(int argc, char * argv[])
{
    if (argc != 4)
    {
        std::cerr << "Usage: " << std::endl;
        std::cerr << argv[0] << " <InputImageFile> <OutputImageFile> <radius>" << std::endl;
        return EXIT_FAILURE;
    }

    constexpr unsigned int Dimension = 3;

    const char * inputFileName = argv[1];
    const char * outputFileName = argv[2];
    const int    radiusValue = std::stoi(argv[3]);

    using PixelType = unsigned char;
    using ImageType = itk::Image<PixelType, Dimension>;

    using ReaderType = itk::ImageFileReader<ImageType>;
    ReaderType::Pointer reader = ReaderType::New();
    reader->SetFileName(inputFileName);

    using FilterType = itk::MeanImageFilter<ImageType, ImageType>;
    FilterType::Pointer meanFilter = FilterType::New();

    FilterType::InputSizeType radius;
    radius.Fill(radiusValue);

    meanFilter->SetRadius(radius);
    meanFilter->SetInput(reader->GetOutput());

    using WriterType = itk::ImageFileWriter<ImageType>;
    WriterType::Pointer writer = WriterType::New();
    writer->SetInput(meanFilter->GetOutput());
    writer->SetFileName(outputFileName);

    try
    {
        writer->Update();
    }
    catch (itk::ExceptionObject & error)
    {
        std::cerr << "Error: " << error << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}