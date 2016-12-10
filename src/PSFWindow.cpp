#include "PSFWindow.h"
#include "ImageDisplay.h"
#include "LogColormap.h"

#include <qwt_plot_spectrocurve.h>

#include <complex>
#include <fftw3.h>

size_t rowmajorindex(size_t r, size_t c, size_t rows, size_t cols)
{
  return (c + r*cols);
}
// org: #define rowmajorindex(i, j, dimx, dimy) (j + dimy*i)

PSFWindow::PSFWindow(QWidget *parent, Qt::WindowFlags flags) :
    QMainWindow(parent, flags),
    imagedisplay_(new ImageDisplay())
{
    setCentralWidget(imagedisplay_);
}

void PSFWindow::keyPressEvent(QKeyEvent* event)
{
    switch (event->key())
    {
    case Qt::Key_S:
        imagedisplay_->toggleColormap();
        break;
    default:
        event->ignore();
        break;
    }
}

void fft2shift(std::complex<float>* img, size_t rows, size_t cols)
{
    if (rows % 2 != 0) throw 0;
    if (cols % 2 != 0) throw 0;

    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < cols; ++c)
        {
            float power = -1;
            int idx = 0;
            while (idx++ < (r + c))
                power *= -1;
            img[rowmajorindex(r, c, rows, cols)] *= power;
        }
}

void PSFWindow::setSamples(const QVector<QwtPoint3D> &samples)
{
  QSize qsize = estimateSize(samples);
  int rows = qsize.height();
  int cols = qsize.width();
  int size = std::max(rows, cols);
    
  std::complex<float>* F = new std::complex<float>[rows*cols];
  memset(F, 0., rows*cols*sizeof(std::complex<float>));
  for (int i = 0; i < samples.size(); ++i)
    {
      F[rowmajorindex((int)(samples[i].y() + rows/2),
		      (int)(samples[i].x() + cols/2),
		      rows, cols)] = 1;
    }
  std::complex<float>* f = new std::complex<float>[rows*cols];

  fftwf_plan ifft2 = fftwf_plan_dft_2d(rows, cols,
				       reinterpret_cast<fftwf_complex*>(F),
				       reinterpret_cast<fftwf_complex*>(f),
				       FFTW_BACKWARD, FFTW_ESTIMATE);

  fft2shift(F, rows, cols);

  fftwf_execute(ifft2);
  fftwf_destroy_plan(ifft2);

  QVector<double> out(size*size);
  float minIntensity = std::abs(f[0]);
  float maxIntensity = minIntensity;

  size_t rOffset = (size - rows)/2;
  size_t cOffset = (size - cols)/2;
  for (int r = rOffset; r < rOffset + rows; ++r)
    for (int c = cOffset; c < cOffset + cols; ++c)
      {
	size_t iout = rowmajorindex(size - r, c, size, size);
        out[iout] = std::abs(f[rowmajorindex(r - rOffset, c - cOffset, rows, cols)]);
        if (out[iout] < minIntensity) minIntensity = out[iout];
        else if (out[iout] > maxIntensity) maxIntensity = out[iout];
      }

  delete [] f;
  delete [] F;

  imagedisplay_->updateDisplay(out, size, size, minIntensity, maxIntensity);
}

QSize PSFWindow::estimateSize(const QVector<QwtPoint3D> &samples) const
{
    QwtPoint3DSeriesData sd(samples);
    QRectF r = sd.boundingRect();
    int cols = 2*std::max(std::fabs(r.right()), std::fabs(r.left()));
    int rows = 2*std::max(std::fabs(r.top()), std::fabs(r.bottom()));

    // forced to even size, which is also necessary for fftshift routine
    return QSize(cols, rows);
}
