using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Scorer : MonoBehaviour
{
    int hits = 0;

    // Start is called before the first frame update
    private void OnCollisionEnter(Collision collision)
    {
        hits++;
        Debug.Log("You've bump in to things %d" + hits);
    }
}
