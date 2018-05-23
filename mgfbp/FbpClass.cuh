#pragma once
#include <string>
#include <vector>

namespace mango
{
	struct Config
	{
		/*********************************************************
		* input and output directory and files
		*********************************************************/
		std::string		inputDir;
		std::string		outputDir;
		std::vector<std::string>	inputFiles;
		std::vector<std::string>	outputFiles;

		bool		saveFilterSinogram;

		/*********************************************************
		* sinogram and slice parameters
		*********************************************************/
		unsigned	sgmWidth;				// sinogram width (number of detector elements)
		unsigned	sgmHeight;				// sinogram height (number of frames)
		unsigned	views;					// number of views for reconstruction
		unsigned	sliceCount;				// number of slice in each sinogram file

		float		detEltSize;				// physical size of detector element [mm]
		float		detOffCenter;			// the position (coordinate) of center of detector

		float		sid;					// source to isocenter distance [mm]
		float		sdd;					// source to detector distance [mm]

		/*********************************************************
		* reconstruction parameters
		*********************************************************/
		unsigned	imgDim;					// number of rows/cols of reconstructed images
		float		pixelSize;				// image pixel size [mm]

		float		imgRot;					// rotate the image [degree]
		
		float		xCenter;				// the center of reconstructed image [x mm, y mm]
		float		yCenter;				// the center of reconstructed image [x mm, y mm]


		std::string	kernelName;				// reconstruction kernel name
		std::vector<float>	kernelParam;	// reconstruction kernel parameters
	};


	class FbpClass
	{
	public:
		static Config config;

	private:
		// array of detector element coordinate
		static float* u;
		// array of each view angle [radius]
		static float* beta;
		// array of reconstruction kernel
		static float* reconKernel;


	private:
		float* sinogram = nullptr;
		float* sinogram_filter = nullptr;
		float* image = nullptr;

	public:
		FbpClass();
		~FbpClass();


		// Read config file
		void ReadConfigFile(const char* filename);

		// Initialize parameters
		void InitParam();

		// Read sinogram file
		void ReadSinogramFile(const char* filename);

		// Save filtered sinogram data to file
		void SaveFilteredSinogram(const char* filename);

		// Save image to file
		void SaveImage(const char* filename);

		// Filter the current sinogram data
		void FilterSinogram();

		// Backproject the image using pixel-driven method
		void BackprojectPixelDriven();

	};


}


