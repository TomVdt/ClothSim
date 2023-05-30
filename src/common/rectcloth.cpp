#include "include/constants.h"
#include "include/exceptions.h"
#include "include/rectcloth.h"
#include "include/vector3d.h"

#include <cmath>

RectCloth::RectCloth(double mass, Vector3D width, Vector3D length, const Vector3D& origin, double lambda, double step, double k, double l0) {
    const double widthNorm(width.norm());
    const double lengthNorm(length.norm());
    width.normalize();
    length.normalize();

    // Colinéaires
    if (width == length or width == -length) {
        ERROR(ValueError, "Width and length vectors must not be colinear");
    }

    // Pas perpendiculaires
    if (std::abs(width.dot(length)) > CONSTANTS::EPSILON) {
        length = ((length - (length.dot(width) * width) / width.normSq()).normalize() * length.norm());
    }

    // Créer les masses
    Vector3D currWidth;
    Vector3D currLength;
    const int lengthCount(lengthNorm / step + 1);
    const int widthCount(widthNorm / step + 1);
    for (int l(0); l < lengthCount; ++l) {
        for (int w(0); w < widthCount; ++w) {
            Vector3D pos(origin + currWidth + currLength);
            addMass(mass, lambda, pos);

            currWidth += step * width;
        }
        currLength += step * length;
        currWidth *= 0;
    }

    // Connecter les masses
    for (int l(0); l < lengthCount; ++l) {
        for (int w(0); w < widthCount; ++w) {
            const int i(l * widthCount + w);
            // "Up"
            if (i - widthCount >= 0) {
                connect(i, i - widthCount, k, l0);
            }
            // "Left"
            if (w > 0) {
                connect(i, i - 1, k, l0);
            }
        }
    }
}
