#include "include/constants.h"
#include "include/renderer.h"
#include "include/rectcloth.h"

#include <cmath>

RectCloth::RectCloth(double mass, Vector3D width, Vector3D length, const Vector3D& origin, double lambda, double massPerunit, double k, double l0) {
    // Pas cohérent
    if (massPerunit < 1.0) {
        // TODO: exceptions
        return;
    }

    // Colinéaires
    if (width.normalized() == length.normalized()) {
        return;
    }

    // Pas perpendiculaires
    if (std::abs(width.dot(length)) > CONSTANTS::EPSILON) {
        length = ((length - (length.dot(width) * width) / width.normSq()).normalize() * length.norm());
    }

    // Créer les masses
    const double widthNorm(width.norm());
    const double lengthNorm(length.norm());
    const double step(lengthNorm / massPerunit);    
    Vector3D currWidth;
    Vector3D currLength;

    width.normalize();
    length.normalize();

    const int lengthCount(massPerunit);
    const int widthCount(widthNorm / step);
    for (int l(0); l < lengthCount; ++l) {
        for (int w(0); w < widthCount; ++w) {
            // TODO: unhardcode this
            Vector3D pos(origin + currWidth + currLength);
            addMass(std::make_unique<Masse>(mass, lambda, pos, Vector3D(0, 0, 0), l == 0));

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
