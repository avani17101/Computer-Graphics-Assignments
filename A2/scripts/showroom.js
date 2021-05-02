class ShowroomInit extends SceneInit {
	constructor(light_spots, spot_left, spot_right, spot_back, spot_front) {
		super();
		this.light_spots = [
			this.spot_front = spot_front,
			this.spot_back = spot_back,
			this.spot_left = spot_left,
			this.spot_right = spot_right
		];		
	}
	setPos() {
		this.light_spots[0].position.set(-100, 10, 0);
		this.light_spots[1].position.set(100, 10, 0);
		this.light_spots[2].position.set(0, 10, -150);
		this.light_spots[3].position.set(0, 70, 150);
	}

	createLights() {
		for (let i = 0; i < this.light_spots.length; ++i) {
			this.light_spots[i] = new THREE.SpotLight();
			Scene.scene.add(this.light_spots[i]);
		}
		this.light_spots[0].position.set(-100, 10, 0);
		this.light_spots[1].position.set(100, 10, 0);
		this.light_spots[2].position.set(0, 10, -150);
		this.light_spots[3].position.set(0, 70, 150);
		
		for (let i = 0; i < this.light_spots.length; ++i) {
			this.light_spots[i].visible = false;
		}
	}


	
}
