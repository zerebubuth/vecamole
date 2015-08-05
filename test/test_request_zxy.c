#include "vecamole.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define ASSERT(p) { if (!(p)) {                          \
    fprintf(stderr, "Assertion (%s) failed at %s:%d.\n", \
            #p, __FILE__, __LINE__);                     \
    return 1;                                            \
    } }

#define ASSERT_APPROX(a, b) { if (fabs((a) - (b)) > 1.0e-6) {       \
      fprintf(stderr, "Assertion %s == %s (approximately) failed. " \
              "%s = %f, %s = %f, difference = %f. At %s:%d.\n",     \
              #a, #b, #a, (a), #b, (b), ((a) - (b)),                \
              __FILE__, __LINE__);                                  \
      return 1;                                                     \
    } }

int check(int z, int x, int y,
          double xmin, double ymin, double xmax, double ymax) {
  double xmin_ = 0.0, ymin_ = 0.0, xmax_ = 0.0, ymax_ = 0.0;
  vecamole_request_t *request = vecamole_request_zxy(256, 256, z, x, y);
  ASSERT(request != NULL);
  ASSERT(vecamole_request_extent(request, &xmin_, &ymin_, &xmax_, &ymax_) == 0);
  ASSERT(vecamole_request_delete(request) == 0);
  ASSERT_APPROX(xmin, xmin_);
  ASSERT_APPROX(xmax, xmax_);
  ASSERT_APPROX(ymin, ymin_);
  ASSERT_APPROX(ymax, ymax_);
  return 0;
}

int check_message(int z, int x, int y,
                  double xmin, double ymin, double xmax, double ymax) {
  int status = check(z, x, y, xmin, ymin, xmax, ymax);
  if (status != 0) {
    fprintf(stderr, "While checking tile %d/%d/%d.\n",
            z, x, y);
  }
  return status;
}

int main(int argc, char *argv[]) {
  ASSERT(check_message(0, 0, 0,
                       -20037508.34, -20037508.34,
                       20037508.34, 20037508.34) == 0);
  ASSERT(check_message(1, 0, 0,
                       -20037508.34, 0.0,
                       0.0, 20037508.34) == 0);
  ASSERT(check_message(2, 1, 1,
                       -10018754.17, 0.0,
                       0.0, 10018754.17) == 0);
  ASSERT(check_message(30, 536870912, 0,
                       0.0, 20037508.3026772,
                       0.0373228, 20037508.34) == 0);

  ASSERT(vecamole_request_zxy(256, 256, -1, 0, 0) == NULL);
  ASSERT(vecamole_request_zxy(256, 256,  0, 1, 1) == NULL);
  ASSERT(vecamole_request_zxy(256, 256,  1, 2, 0) == NULL);
  ASSERT(vecamole_request_zxy(256, 256,  1, 0, 2) == NULL);
  ASSERT(vecamole_request_zxy(256, 256, 31, 0, 0) == NULL);

  return 0;
}
