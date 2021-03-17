/*


    Source: https://www.tutorialspoint.com/design_pattern/facade_pattern.html


 */

@FacadeAnnotation(name = "Shape", clientAccessible = false)
interface Shape
{
    void draw();
}

// concrete classes implementing the same interface
@FacadeAnnotation(name = "Rectangle", clientAccessible = false)
class Rectangle implements Shape
{
    @Override
    public void draw()
    {
        System.out.println("Rectangle::draw()");
    }
}

@FacadeAnnotation(name = "Square", clientAccessible = false)
class Square implements Shape
{

    @Override
    public void draw()
    {
        System.out.println("Square::draw()");
    }
}

@FacadeAnnotation(name = "Circle", clientAccessible = false)
class Circle implements Shape
{

    @Override
    public void draw()
    {
        System.out.println("Circle::draw()");
    }
}

@FacadeAnnotation(name = "ShapeFacade", clientAccessible = true)
public class ShapeFacade
{
    private Shape circle;
    private Shape rectangle;
    private Shape square;

    @FacadeAnnotation(name = "ShapeFacade.constructor", clientAccessible = true)
    public ShapeFacade()
    {
        // polymorphism at hand here:
        // LHS = RHS, so LHS has functionalities of RHS
        // i.e. they will print out their respect names
        circle = new Circle();
        circle.draw();
        rectangle = new Rectangle();
        rectangle.draw();
        square = new Square();
        square.draw();
    }

    public void drawCircle()
    {
        circle.draw();
    }
    public void drawRectangle()
    {
        rectangle.draw();
    }
    public void drawSquare()
    {
        square.draw();
    }
}