#include "PSFWindow.h"
#include "ImageDisplay.h"

#include <complex>
#include <fftw3.h>

PSFWindow::PSFWindow(QWidget *parent, Qt::WindowFlags flags) :
  QMainWindow(parent, flags),
  imagedisplay_(new ImageDisplay())
{
  setCentralWidget(imagedisplay_);
}

void PSFWindow::keyPressEvent(QKeyEvent* event)
{
}

#define rowmajorindex(i, j,dimx, dimy) (j + dimy*i)

void fft2shift(std::complex<float>* img, size_t size)
{
  if (size % 2 != 0) throw 0;
  
  for (int j = 0; j < size; ++j)
    for (int i = 0; i < size; ++i)
      {
	float power = -1;
	int idx = 0;
	while (idx++ < (i + j))
	  power *= -1;
	img[rowmajorindex(i, j, size, size)] *= power;
      }
}

void PSFWindow::setSamples(const QVector<QwtPoint3D> &samples)
{
  int size = estimateSize(samples);

  std::complex<float>* F = new std::complex<float>[size*size];
  memset(F, 0., size*size*sizeof(std::complex<float>));
  for (int i = 0; i < samples.size(); ++i)
    {
      F[rowmajorindex((int)(samples[i].x() + size/2),
		      (int)(samples[i].y() + size/2),
		      size, size)] = 1;
    }
  std::complex<float>* f = new std::complex<float>[size*size]; 

  fftwf_plan ifft2 = fftwf_plan_dft_2d(size, size,
				       reinterpret_cast<fftwf_complex*>(F),
				       reinterpret_cast<fftwf_complex*>(f),
				       FFTW_BACKWARD, FFTW_ESTIMATE);

  fft2shift(F, size);
  
  fftwf_execute(ifft2);
  fftwf_destroy_plan(ifft2);
  
  QVector<double> out(size*size);
  float minIntensity = std::abs(f[0]);
  float maxIntensity = minIntensity;
  for (size_t i = 0; i < size*size; ++i)
    {
      out[i] = std::abs(f[i]);
      if (out[i] < minIntensity) minIntensity = out[i];
      else if (out[i] > maxIntensity) maxIntensity = out[i];
    }
  
  delete [] f;
  delete [] F;

  imagedisplay_->updateDisplay(out, size, size, minIntensity, maxIntensity);
}

int PSFWindow::estimateSize(const QVector<QwtPoint3D> &samples) const
{
  return 128;
}


