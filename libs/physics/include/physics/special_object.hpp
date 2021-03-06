#pragma once

#include <physics/interface.hpp>
#include <math.hpp>

namespace physics {

class EnginesIndexedObject {
  public:
    EnginesIndexedObject();

    virtual ~EnginesIndexedObject() = default;

    friend class StoreObjects;

  protected:
    ssize_t _index;
};

class AcceleratableObject {
  public:
    AcceleratableObject();

    [[nodiscard]]
    bool have_some_impulse() const noexcept;

    [[nodiscard]]
    math::decimal_t target_impulse() const noexcept;

    void add_impulse(math::decimal_t target);

    void complete_add_impulse();

    virtual ~AcceleratableObject() = default;

  private:
    bool _need_impulse;
    math::decimal_t _target_impulse;
};

class ColideObject : public math::IPositionable, public math::IRotatable {
  public:
    ColideObject() = delete;

    explicit ColideObject(std::unique_ptr<math::Polygon> &&polygon);

    [[nodiscard]]
    bool is_colides(const ColideObject &object) const;

    [[nodiscard]]
    math::coords_t get_pos() const noexcept final;

    void set_pos(math::coords_t pos) final;

    [[nodiscard]]
    math::decimal_t get_rotation() const noexcept override;

    void rotate(math::decimal_t offset_angle) override;

    void set_rotation(math::decimal_t angle) override;

    [[nodiscard]]
    std::unique_ptr<math::Polygon> &get_polygon();

    [[nodiscard]]
    const std::unique_ptr<math::Polygon> &get_polygon() const;

  protected:
    std::unique_ptr<math::Polygon> _polygon;
};


}  // namespace physics
