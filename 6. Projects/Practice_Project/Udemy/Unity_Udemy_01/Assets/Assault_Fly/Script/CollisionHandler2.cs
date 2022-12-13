using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CollisionHandler2 : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    void OnCollisionEnter(Collision collision)
    {
        Debug.Log(this.name + " Collisioned with!!" + collision.gameObject.name);
    }

    private void OnTriggerEnter(Collider other)
    {
        Debug.Log($"{this.name} ** Triggered by ** {other.gameObject.name}");
    }
}
