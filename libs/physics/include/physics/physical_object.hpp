#pragma once

#include <memory>

#include <physics/special_object.hpp>
#include <physics/interface.hpp>
#include <math.hpp>

namespace physics {

class PhysicalObject : public EnginesIndexedObject, public ColideObject,
                       public AcceleratableObject {
  public:
    PhysicalObject() = delete;

    explicit PhysicalObject(std::unique_ptr<math::Polygon> &&polygon);

    explicit PhysicalObject(std::unique_ptr<math::Polygon> &&polygon,
                            math::coords_t pos, math::Vector2d velocity,
                            size_t weight, bool have_effective_orbit = true);

    [[nodiscard]]
    size_t get_weight() const noexcept;

    [[nodiscard]]
    math::decimal_t get_cast_weight() const noexcept;

    [[nodiscard]]
    const math::Vector2d &get_velocity() const noexcept;

    void set_velocity(math::Vector2d velocity);

    void set_weight(size_t weight);

    bool have_effective_orbit() const;

    ~PhysicalObject() override = default;

  private:
    size_t _weight;
    math::Vector2d _velocity;
    bool _have_effective_orbit;
};

}  // namespace physics
