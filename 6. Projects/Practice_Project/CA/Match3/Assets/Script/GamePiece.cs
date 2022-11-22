using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GamePiece : MonoBehaviour
{
    private int x;
    private int y;
    private Grid grid;
    private Grid.PieceType type;
    private MovablePiece movableComponent;
    public ColorPiece colorComponent;

    public int X
    {
        get { return x; } 
        set { if (IsMovable()) x = value; }
    }
    public int Y
    {
        get { return y; }
        set { if (IsMovable()) y = value; }

    }
    public Grid.PieceType Type
    {
        get { return type; }
    }
    public Grid GridRef
    {
        get { return grid; }
    }

    public MovablePiece MovableComponent
    {
        get { return movableComponent; }
    }
    public ColorPiece ColorComponent
    {
        get { return colorComponent; }
    }
    private void Awake()
    {
        movableComponent = GetComponent<MovablePiece>();
        colorComponent = GetComponent<ColorPiece>();
    }


    void Start()
    {
        
    }

    void Update()
    {
        
    }

    public void Init(int _x, int _y, Grid _grid, Grid.PieceType _type)
    {
        x = _x;
        y = _y;
        grid = _grid;
        type = _type;
    }

    private void OnMouseEnter()
    {
        grid.EnterPiece(this);   
    }
    private void OnMouseDown()
    {
        grid.PreddPiece(this);
    }
    private void OnMouseUp()
    {
        grid.ReleasePiece();
    }

    public bool IsMovable()
    {
        return movableComponent != null;
    }

    public bool IsColored()
    {
        return colorComponent != null;
    }


}
