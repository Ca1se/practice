# Formulas to remember
## Common equivalent infinitesimal
$$
    (1 + x)^\alpha \sim \alpha x \\
    \log_a(1 + x) \sim \frac{x}{\ln{a}} \\
    x - \ln(1 + x) \sim \frac{1}{2}x^2 \\
    \ln(x + \sqrt{1 + x^2}) \sim x \\
    x - \sin{x} \sim \frac{1}{6}x^3 \\
    \tan{x} - x \sim \frac{1}{3}x^3 \\
    \arcsin{x} - x \sim \frac{1}{6}x^3 \\
    x - \arctan{x} \sim \frac{1}{3}x^3 \\
    \tan{x} - \sin{x} \sim \frac{1}{2}x^3 \\
$$
## Common integrals
$$
    \int{\tan{x}}dx = -\ln{|\cos{x}|} + C \\
    \int{\sec{x}}dx = \ln{|\sec{x} + \tan{x}|} + C \\
    \int{\csc{x}}dx = \ln{|\csc{x} - \cot{x}|} + C \\
    \int{\sec^2{x}}dx = \tan{x} + C \\
    \int{\csc^2{x}}dx = -\cot{x} + C \\
    \int{\frac{1}{a^2 + x^2}}dx = \frac{1}{a}\arctan{\frac{x}{a}} + C \\
    \int{\frac{1}{\sqrt{a^2 - x^2}}}dx = \arcsin{\frac{x}{a}} + C \\
    \int{\frac{1}{\sqrt{x^2 - a^2}}}dx = \ln{(x + \sqrt{x^2 - a^2})} + C \\
    \int{\frac{1}{\sqrt{x^2 + a^2}}}dx = \ln{(x + \sqrt{x^2 + a^2})} + C \\
    \int{\frac{1}{x^2 - a^2}}dx = \frac{1}{2a}\ln{|\frac{x - a}{x + a}|} + C \\
    \int{\sqrt{a^2 - x^2}}dx = \frac{a^2}{2}\arcsin{\frac{x}{a}} + \frac{x}{2}\sqrt{a^2 - x^2} + C \\
    \int{\tan^2{x}}dx = \tan{x} - x + C \\
    \int{\cot^2{x}}dx = -\cot{x} - x + C
$$
## Some conclusions
$when~ n \to +\infty:$
$$
    if~ a = -1,~ then~ 1 + \frac{1}{2} + \frac{1}{3} + ... + \frac{1}{n}~ \sim~ \ln{n} \newline
    if~ a > -1,~ then~ 1^a + 2^a +3^a + ... + n^a~ \sim~ \frac{1}{a + 1}n^{a+1}\newline
    if~ a < -1,~ then~ 1^a + 2^a +3^a + ... + n^a~ converge
$$
## Trigonometric identities
$$
    \sin^3\theta = \frac{3\sin{\theta} - \sin{3\theta}}{4} \newline
    \cos^3\theta = \frac{3\cos{\theta} + \cos{3\theta}}{4} \newline
    \sin{\alpha}\cos{\beta} = \frac{\sin{(\alpha + \beta)} + \sin{(\alpha - \beta)}}{2} \newline
    \cos{\alpha}\cos{\beta} = \frac{\cos{(\alpha + \beta)} + \cos{(\alpha - \beta)}}{2} \newline
    \sin{\alpha}\sin{\beta} = -\frac{\cos{(\alpha + \beta)} - \cos{(\alpha - \beta)}}{2} \newline
$$