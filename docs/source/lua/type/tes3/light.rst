
Light
========================================================

This interface represents a light source game object.


Properties
--------------------------------------------------------

**id** (`string`_)
    The object's unique id.

**objectType** (`number`_)
    The object's `objectType`_

**sourceMod** (`string`_)
    The object's originating plugin filename.

**mesh** (`string`_)
    The object's mesh path, relative to 'Data Files/Meshes'.

**boundingBox** (`boundingBox`_)
    The object's `boundingBox`_.

**icon** (`string`_)
    The object's icon path, relative to 'Data Files/Icons'.

**name** (`string`_)
    The object's name.

**script** (`userdata`_)
    The object's script.

**value** (`number`_)
    The object's value in gold.

**weight** (`number`_)
    The object's weight.

**time** (`number`_)
    The time this light will last while equipped by the player.

**sound** (`number`_)
    The sound that loops while the light is equipped.

**radius** (`number`_)
    The radius in which the light will affect other objects.

**canCarry** (`boolean`_)
    Description Here

**flickers** (`boolean`_)
    Description Here

**flickersSlowly** (`boolean`_)
    Description Here

**isDynamic** (`boolean`_)
    Description Here

**isFire** (`boolean`_)
    Description Here

**isNegative** (`boolean`_)
    Description Here

**isOffByDefault** (`boolean`_)
    Description Here

**pulses** (`boolean`_)
    Description Here

**pulsesSlowly** (`boolean`_)
    Description Here

Methods
--------------------------------------------------------

`number`_ **getTimeLeft** (`tes3equipmentStack`_ x)
    ..

`number`_ **getTimeLeft** (`Reference`_ x)
    Returns:
        The time left until the light burns out, in seconds. It is a float, so many need to be rounded with ``math.floor`` before display.

    Retrieves the remaining lifetime of this light, given the equipment stack or reference that owns it.


--------------------------------------------------------

.. _`boolean`: ../lua/boolean.html
.. _`number`: ../lua/number.html
.. _`string`: ../lua/string.html
.. _`table`: ../lua/table.html
.. _`userdata`: ../lua/userdata.html

.. _`objectType`: baseObject/objectType.html
.. _`boundingBox`: physicalObject/boundingBox.html
.. _`tes3equipmentStack`: equipmentStack.html
.. _`Reference`: reference.html