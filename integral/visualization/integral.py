# /**----------------------------------------------------------*
#  * first version: 2024/12/22                                 *
#  * github: https://github.com/sanoesogood                    *                              
#  *----------------------------------------------------------**/

import matplotlib.pyplot as plt
import numpy as np

def circle(x):
  return (100 - x**2)**0.5

def ellipse(x):
  return (225 - 9*x**2)**0.5

x_i, x_f = -5, 5
n = 2001

x_val_circle = np.linspace(-10, 10, n)
x_val_ellipse = np.linspace(-5, 5, n)

x_val_int, dx = np.linspace(x_i, x_f, n, retstep=True)
y_val_int = []
area = []

# calculate part
for x in x_val_int:
  y = ellipse(x) if ellipse(x) < circle(x) else circle(x)
  y_val_int.append(y)
  area.append(y * dx)

# visualization part
print(f"area = {2 * sum(area)}")

fig = plt.figure(figsize=(5, 5))
ax = plt.subplot()

ax.set_xlim(-15, 15)
ax.set_ylim(-15, 15)

x_val_circle = np.linspace(-10, 10, n)
ax.plot(x_val_circle, circle(x_val_circle), color="black")
ax.plot(x_val_circle, -circle(x_val_circle), color="black")
ax.plot(x_val_ellipse, ellipse(x_val_ellipse), color="black")
ax.plot(x_val_ellipse, -ellipse(x_val_ellipse), color="black")

ax.plot(x_val_int, y_val_int, color="red")
ax.plot(x_val_int, [-y for y in y_val_int], color="red")

ax.fill_between(x_val_int, y_val_int, where=(y_val_int >= circle(x_val_circle)), color="b")
ax.fill_between(x_val_int, [-y for y in y_val_int], where=([-y for y in y_val_int] <= circle(x_val_circle)), color="b")

plt.show()