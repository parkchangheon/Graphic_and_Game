using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ClearablePiece : MonoBehaviour
{

    private bool isBeingCleared = false;
    public bool IsBeingCleared
    {
        get { return isBeingCleared; }
    }

    protected GamePiece piece;

    private void Awake()
    {
        piece = GetComponent<GamePiece>();

    }


    void Start()
    {
        
    }

    void Update()
    {
        
    }

    public void Clear()
    {
        isBeingCleared = true;
        Destroy(gameObject);
    }


}
